#include "movingobject.h"


MovingObject::MovingObject(int posX, int posY, int length, int height, objectType type, collisionType colType, int speedX, int speedY) : GameObject(posX, posY, length, height, type, colType) {
    this->speedX = speedX;
    this->speedY = speedY;
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

void MovingObject::updatePosition() {

}
