#include "shoot.h"

/**
 * @brief Konstruktor für einen Schuss(Bierkrug)
 * @param posX      : x-Position
 * @param posY      : y-Position
 * @param length    : Länge         //Unnötig
 * @param height    : Höhe          //Unnötig
 * @param speedX    : horizontale Geschwindigkeit
 * @param origin    : Schuss Erzeuger
 * @author Johann
 */
//Da Länge und Breite konstante Werte beim Bierkrug sind, zur Zeit nur Optinal
Shoot::Shoot(int posX, int posY, int length, int height, int speedX, objectType origin) : MovingObject(posX, posY, length, height, shot, travesing, speedX, 0) {
    inflictedDamage = 10;
    this->origin = origin;
}

Shoot::~Shoot() {

}

/**
 * @brief Shoot::getInflictedDamage
 * gibt den Schaden den der Schuss zufügt zurück
 * @return Schaden
 * @author Johann
 */
int Shoot::getInflictedDamage() const {
    return inflictedDamage;
}

void Shoot::update() {
    //posX = posX + this->getSpeedX();
    updatePosition();
}
