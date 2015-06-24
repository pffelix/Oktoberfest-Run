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
Shoot::Shoot(int posX, int posY, int direction, objectType origin) : MovingObject((posX + (playerScale / 2)), (posY + playerScale), shot, (direction * 2 * maxSpeed) , 0) {
    inflictedDamage = 1;
    this->origin = origin;

    //Grafik - Attackgrafik initialisieren
    setPixmap(QPixmap(":/images/images/attack.png"));
    setPos(getPosX() - getLength()*0.5, yOffset - getPosY() - getHeight());
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
