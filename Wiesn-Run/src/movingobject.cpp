#include "movingobject.h"

MovingObject::MovingObject() {
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
