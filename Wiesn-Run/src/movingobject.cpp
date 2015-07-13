#include "movingobject.h"
#include "player.h"
#include <QTransform>


MovingObject::MovingObject(int posX, int posY, objectType type, int speedX, int speedY) : GameObject(posX, posY, type) {
    this->speedX = speedX;
    this->speedY = speedY;

}
MovingObject::~MovingObject() {

}

void MovingObject:: setPosX(int posX) {
    this->posX = posX;
}

void MovingObject::setPosY(int posY) {
    this->posY = posY;
}

int MovingObject::getSpeedX() const {
    return speedX;
}

int MovingObject::getSpeedY() const {
    return speedY;
}

void MovingObject::setSpeedX(int speedX) {
    this->speedX = speedX;
}

void MovingObject::setSpeedY(int speedY) {
    this->speedY = speedY;
}


// Ist schon im Header mit =0 beschrieben
/*void MovingObject::update() {

}*/

/**
 * @brief überschreibt die X und Y Position gemäß SpeedXY
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
 * Wenn der Spieler in der Luft ist bzw. springt setzt die Animation aus
 * @Author Flo
 */
void MovingObject::swapImage()
{
    //Tourist für frameRate/2 Frames in Bewegung seit letztem Bildwechsel?
    if (getType() == enemy_tourist && framesDirection%(frameRate/2) == 0 && speedX != 0) {

        if(imageState == true) {
            setPixmap(QPixmap(":/images/images/tourist2.png"));
            imageState = false;
        }
        else {
            setPixmap(QPixmap(":/images/images/tourist1.png"));
            imageState = true;
        }
    }

    //Spieler für  frameRate/2 Frames in Bewegung seit letztem Bildwechsel und nicht in der Luft?
    else if (getType() == player && framesDirection%(frameRate/2) == 0 && speedX != 0
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


