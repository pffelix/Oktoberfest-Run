#include "movingobject.h"
#include "player.h"
#include <QTransform>

/**
 * @brief Konstruktor für ein MovingObject. Als abstrakte Klasse kann MovingObject nicht instanziert werden.
 * Alle Attribute für diese Klasse müssen von den erbenden Klassen übergeben werden
 *
 * @param posX X-Position im Spiel
 * @param posY Y-Position im Spiel
 * @param type Objekt-Typ
 * @param speedX horizontale Geschwindigkeit, >0 entspricht einer Bewegung nach rechts
 * @param speedY vertikale Geschwindigkeit, >0 entspricht einer Bewegung nach oben
 *
 * @author Johann, Simon
 */
MovingObject::MovingObject(int posX, int posY, objectType type, int speedX, int speedY) : GameObject(posX, posY, type) {
    this->speedX = speedX;
    this->speedY = speedY;

}

/**
 * @brief Destruktor
 */
MovingObject::~MovingObject() {

}

/**
 * @brief Setzt die X-Position des Objekts.
 *
 * @param Position
 */
void MovingObject:: setPosX(int posX) {
    this->posX = posX;
}

/**
 * @brief Setzt die Y-Position des Objekts.
 *
 * @param Position
 */
void MovingObject::setPosY(int posY) {
    this->posY = posY;
}

/**
 * @brief Gibt die horizontale Geschwindigkeit zurück.
 *
 * @return int
 */
int MovingObject::getSpeedX() const {
    return speedX;
}

/**
 * @brief Gibt die vertikale Geschwindigkeit zurück.
 *
 * @return int
 */
int MovingObject::getSpeedY() const {
    return speedY;
}

/**
 * @brief Setzt die horizontale Geschwindigkeit.
 *
 * @param speedX horizontale Geschwindigkeit
 */
void MovingObject::setSpeedX(int speedX) {
    this->speedX = speedX;
}

/**
 * @brief Setzt die vertikale Geschwindigkeit.
 *
 * @param speedY vertikale Geschwindigkeit
 */
void MovingObject::setSpeedY(int speedY) {
    this->speedY = speedY;
}

/**
 * @brief überschreibt die X und Y Position gemäß SpeedXY.
 *
 * @author Rupert
 */
void MovingObject::updatePosition() {
    setPosX(getPosX() + getSpeedX());
    if ((posY < 5) && (speedY < 0)) {
        posY = 0;
    } else {
        setPosY(getPosY() + getSpeedY());
    }

}

/**
 * @brief aktualisiert die Anzahl der Frames für die ein Object ununterbrochen in eine Richtung gelaufen ist
 * Wenn das Objekt steht oder die Richtung wechselt wird FramesDirection auf 0 gesetzt, ansonsten je nach Richtung
 * um eins erhöht (vorwärts) oder um eins erniedrigt (rückwärts).
 * So lässt sich auch die Richtung abfragen (> || < als 0) und mit dem aktuellen speedX-Wert ein Richtungswechsel festellen
 *
 * @author Flo
 */
void MovingObject::updateFramesDirection() {
    //Objekt läuft vorwärts?
    if (speedX > 0) {
        //Richtungswechsel?
        if (framesDirection < 0) {
            framesDirection = 0;
        }
        framesDirection ++;
    }

    //Objekt läuft zurück?
    else if(speedX < 0) {
        //Richtungswechsel?
        if (framesDirection > 0) {
            framesDirection = 0;
        }
        framesDirection --;
    }

    //Objekt steht?
    else {
        framesDirection = 0;
    }
}

/**
 * @brief spiegelt Grafiken an der Y-Achse
 * kopiert von "https://forum.qt.io/topic/18131/solved-flip-a-qgraphicssvgitem-on-its-center-point/2" und angepasst.
 * Ermöglicht das Spiegeln von Bildern über eine Transformationsmatrix.
 * Am Anfang wird getestet ob ein Richtungswechsel statt gefunden hat.
 *
 * @author Flo
 */
void MovingObject::flipHorizontal()
{
    //Richtungswechsel hat statt gefunden ?
    if( (speedX > 0 && framesDirection < 0) || (speedX < 0 && framesDirection > 0) ) {

        // Get the current transform
        QTransform transform(this->transform());

        qreal m11 = transform.m11();    // Horizontal scaling
        qreal m31 = transform.m31();    // Horizontal Position (DX)

        // We need this in a minute
        qreal scale = m11;

        // Horizontal flip
        m11 = -m11;

        // Re-position back to origin
        if(m31 > 0)
            m31 = 0;
        else
            m31 = (boundingRect().width() * scale);

        // Write back to the matrix
        transform.setMatrix(m11, 0, 0, 0, 1, 0, m31, 0, 1);

        // Set the items transformation
        setTransform(transform);
    }
}

/**
 * @brief MovingObject::swapImage
 * Die Funktion testet mit Hilfe von "imageState" welches Bild gerade aktiv ist und wechselt dann jeweils auf das andere
 * Bild für die Bewegungsanimation. Es wird alle framRate/2 Frames gewechselt und sofort beim loslaufen.
 * Wenn der Spieler in der Luft ist bzw. springt setzt die Animation aus, wenn er nur noch ein Leben hat läuft
 * sie doppelt so schnell ab.
 *
 * @author Flo
 */
void MovingObject::swapImage()
{
    //Wechselgeschwindigkeit
    int swapSpeed = static_cast<int>(frameRate/2);
    //Tourist für frameRate/2 Frames in Bewegung seit letztem Bildwechsel?
    if (getType() == enemy_tourist && framesDirection%swapSpeed == 0 && speedX != 0) {

        if(imageState == true) {
            setPixmap(QPixmap(":/images/images/tourist2.png"));
            imageState = false;
        }
        else {
            setPixmap(QPixmap(":/images/images/tourist1.png"));
            imageState = true;
        }
    }

    //Spieler nur noch ein Leben?
    if(getType() == player && dynamic_cast<Player*>(this)->getHealth() == 1) {
        swapSpeed = static_cast<int>(frameRate/4);
    }
    //Spieler für  frameRate/2 Frames in Bewegung seit letztem Bildwechsel und nicht in der Luft?
    if (getType() == player && framesDirection%swapSpeed == 0 && speedX != 0
        &&  dynamic_cast<Player*>(this)->inJump() == false) {

        if(imageState == true) {
            setPixmap(QPixmap(":/images/images/player2.png"));
            imageState = false;
        }
        else {
            setPixmap(QPixmap(":/images/images/player1.png"));
            imageState = true;
        }
    }
}


