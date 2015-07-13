#include "shoot.h"

/**
 * @brief Konstruktor für einen Schuss(Bierkrug).
 * Erzeugt einen fliegenden Bierkrug, dabei werden alle Werte gesetzt. Diese können später nur noch ausgelesen und nicht mehr geändert werden.
 * Es gilt, dass ein Bierkrug dreimal so schnell fliegt wie sich der Spieler bewegen kann.
 * Bei der Erzeugung eines Schusses nur die Richtung entscheidend ist. >0 bedeutet nach Rechts
 *
 * @param posX X-Position im Level
 * @param posY Y-Position im Level
 * @param direction Richtung, in die der Bierkrug fliegen soll
 * @param origin Schuss-Erzeuger
 *
 * @author Johann, Simon
 */
//Da Länge und Breite konstante Werte beim Bierkrug sind, zur Zeit nur Optinal
Shoot::Shoot(int posX, int posY, int direction, objectType origin) : MovingObject((posX + (playerScale / 2)), (posY + playerScale), shot, (direction * 3 * maxSpeed) , 0) {
    inflictedDamage = 1;
    harming = true;
    this->origin = origin;
}

/**
 * @brief Destruktor
 */
Shoot::~Shoot() {

}

/**
 * @brief Gibt den Ursprung des Bierkrugs zurück.
 *
 * @return objectType
 */
objectType Shoot::getOrigin() {
    return origin;
}

/**
 * @brief Gibt den Schaden zurück, den der Bierkrug zufügt.
 *
 * @return int
 */
int Shoot::getInflictedDamage() const {
    return inflictedDamage;
}

/**
 * @brief Setzt den Wert, damit der Schuss keinen Schaden mehr zufügt.
 * Dies ist wichtig, damit man nicht zwei Gegner mit einem Bierkrug besiegen kann.
 */
void Shoot::setToDelete() {
    harming = false;
}

/**
 * @brief Gibt zurück, ob der Bierkrug noch Schaden zufügt
 * @return true, wenn der Bierkrug noch nichts getroffen hat und Schaden zufügt
 */
bool Shoot::getHarming() const {
    return harming;
}

/**
 * @brief Die Funktion aktualisiert die Position des Bierkruges
 */
void Shoot::update() {
    updatePosition();
}
