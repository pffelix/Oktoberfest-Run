#include "movingobject.h"


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
