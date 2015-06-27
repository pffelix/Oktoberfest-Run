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

