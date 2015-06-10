#include "shoot.h"

Shoot::Shoot(posX, posY, length, hight, collisiontype, type, speedX, speedY) {
    MovingObject(posX, posY, length, hight, collisiontype, type, speedX, speedY);
    inflictedDamage = 10;
}

Shoot::~Shoot() {

}

int Shoot::getInflictedDamage() const {
    return inflictedDamage;
}

virtual void Shoot::update() {
    //Bewegung durchführen
    posX = posX + this->getSpeedX();
}
