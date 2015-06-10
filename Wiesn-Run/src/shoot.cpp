#include "shoot.h"

Shoot::Shoot(int posX, int posY, int length, int height, objectType type, collisionType colType, int speedX, int speedY) : MovingObject(posX, posY, length, height, type, colType, speedX, speedY) {
    inflictedDamage = 10;
}

Shoot::~Shoot() {

}

int Shoot::getInflictedDamage() const {
    return inflictedDamage;
}

void Shoot::update() {
    posX = posX + this->getSpeedX();
}
