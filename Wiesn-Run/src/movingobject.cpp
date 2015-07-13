#include "movingobject.h"
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

void MovingObject::setFramesDirection(int framesDirection) {
    this->framesDirection = framesDirection;
}

int MovingObject::getFramesDirection() {
    return framesDirection;
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
 * @brief spiegelt Grafiken an der Y-Achse
 * kopiert von https://forum.qt.io/topic/18131/solved-flip-a-qgraphicssvgitem-on-its-center-point/2 und angepasst.
 * Ermöglicht das Spiegeln von Bildern über eine Transformationsmatrix.
 * @author Flo
 */
void MovingObject::flipHorizontal()
{
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

/**
 * @brief MovingObject::swapImage
 * Die Funktion testet mit Hilfe von "imageState" welches Bild gerade aktiv ist und wechselt dann jeweils auf das andere
 * Bild für die Bewegungsanimation.
 * @Author Flo
 */
void MovingObject::swapImage()
{
    switch (getType()) {
    case enemy_tourist: {
        if(imageState == true) {
            setPixmap(QPixmap(":/images/images/tourist2.png"));
            imageState = false;
        }
        else {
            setPixmap(QPixmap(":/images/images/tourist1.png"));
            imageState = true;
        }
        break;
    }
    case player: {
        if(imageState == true) {
            setPixmap(QPixmap(":/images/images/player2.png"));
            imageState = false;
        }
        else {
            setPixmap(QPixmap(":/images/images/player1.png"));
            imageState = true;
        }
        break;
    }
    default: {
        break;
    }
    }
}


