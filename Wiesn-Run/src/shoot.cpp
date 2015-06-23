#include "shoot.h"

/**
 * @brief Konstruktor für einen Schuss(Bierkrug)
 * @param posX      : x-Position
 * @param posY      : y-Position
 * @param speedX    : horizontale Geschwindigkeit
 * @param origin    : Schuss Erzeuger
 *
 * @lastChanges Größe des Bierkruges festgesetzt (erste idee)
 *
 * @author Johann
 */
//Da Länge und Breite konstante Werte beim Bierkrug sind, zur Zeit nur Optinal
Shoot::Shoot(int posX, int posY, int speedX, objectType origin) : MovingObject(posX, posY, 3, 5, shot, speedX, 0) {
    inflictedDamage = 10;
    this->origin = origin;
}

Shoot::~Shoot() {

}

/**
 * @brief Shoot::getOrigin
 * gibt den Ursprung des Bierkrugs zurück, Wer hat ihn geworfen (Player/Enemy)
 * @return Ursprung des Bierkruges
 * @author Johann
 */
objectType Shoot::getOrigin() {
    return origin;
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
