#include "shoot.h"

Shoot::Shoot() {
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
