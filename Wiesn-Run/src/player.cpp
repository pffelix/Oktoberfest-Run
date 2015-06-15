#include "player.h"

/// Class Player
/// lastUpdate: update() 10.6 Johann

Player::Player(int posX, int posY, int length, int height, objectType type, collisionType colType, int speedX, int speedY) : MovingObject(posX, posY, length, height, type, colType, speedX, speedY) {
    health = 100;
    alcoholLevel = 10;
    jumpActive = false;
    jumpTableIndex = 0;
    ammunation = 0;
    immunityCooldown = 0;
    fireRate = 20;
    fireCooldown = 0;
}

Player::~Player() {

}

/**
 * @brief Player::getHealth
 * Gibt aktuellen Lebensstand zurück
 *
 * @return : Lebensstand
 */
int Player::getHealth() const{
    return health;
}

/**
 * @brief Player::setHealth
 * Lebensstand des Spielers wird gesetzt
 *
 * @param health
 * Lebensstand auf den der Spieler gesetzt wird
 */
void Player::setHealth(int health) {
    this->health = health;
}

/**
 * @brief Player::getAlcoholLevel
 * Gibt den Pegel des Spielers zurück
 *
 * @return : Alkoholpegel
 */
int Player::getAlcoholLevel() const {
    return alcoholLevel;
}

/**
 * @brief Player::increaseAlcoholLevel
 * AlkoholPegel wird erhöht.
 *
 * @param additionalAlcohol
 * Wert um den erhöht wird
 */
void Player::increaseAlcoholLevel(int additionalAlcohol) {
    //MaximalWerte
    alcoholLevel = alcoholLevel + additionalAlcohol;
}

/**
 * @brief Player::decreaseAlcoholLevel
 * verringert den Pegel des Spielers
 *
 * @param decreaseLevel
 * Wert um den der Pegel verringert wird
 *
 * @return
 * Gibt an Ob der Alkoholpegel  auf Null fällt
 */
bool Player::decreaseAlcoholLevel(int decreaseLevel) {
    alcoholLevel = alcoholLevel - decreaseLevel;
    if (alcoholLevel > 0) {
        return false;
    } else {
        return true;
    }
    //Spiel ist zu Ende, wenn Alkoholpegel aufgebraucht
}

/**
 * @brief Player::getAmmunatiuon
 * Gibt verbleibende Munition zurück
 *
 * @return : verbleibende Munition
 */
int Player::getAmmunatiuon() const {
    return ammunation;
}

/**
 * @brief Player::increaseAmmunation
 * erhöht die verbleibende Munition des Spielers um 1
 */
void Player::increaseAmmunation() {
    ammunation = ammunation + 1;
}

/**
 * @brief Player::decreaseAmmunation
 * verringert die verbleibende Munition des Spielers um 1
 */
void Player::decreaseAmmunation() {
    ammunation = ammunation - 1;
}

/**
 * @brief Player::getImmunityCooldown
 * @return
 */
int Player::getImmunityCooldown() const {
    return immunityCooldown;
}

/**
 * @brief Player::setImmunityCooldown
 * Zahl der Frames für Unverwundbarkeit wird gesetzt
 *
 * @param immunityCooldown
 * Zahl der Frames
 */
void Player::setImmunityCooldown(int immunityCooldown) {
    this->immunityCooldown = immunityCooldown;
}

/**
 * @brief Player::setJump
 * wechselt den Sprung-Zustand des Spielers
 *
 * @param jump : neuer Sprung-Zustand
 */
void Player::setJump(bool jump) {
    jumpActive = jump;
}

/**
 * @brief Player::setFall
 * wechselt den Sprung-Zustand des Spielers
 * initialisiert einen Fall
 */
void Player::setFall() {
    jumpActive = true;
    jumpTableIndex = fallIndex;
}

/**
 * @brief Player::resetJump
 * setzt den Sprung-Zustand auf anfangfwerte zurück
 */
void Player::resetJump() {
    jumpActive = false;
    jumpTableIndex = 0;
}

/**
 * @brief Player::update
 * führt die Bewegung des Spielers aus (über updatePosition) und verringert Cooldown-Variablen
 */
void Player::update() {
    //Bewegung ausführen
    updatePosition();
    //posX = posX + this->getSpeedX(); // das passiert in updatePosition
    if (jumpActive) {
        //posY = posY + jumpTable[jumpTableIndex]; // jumpTable enthält Geschwindigkeiten, die werden in updatePosition berücksichtigt
        setSpeedY(jumpTable[jumpTableIndex]);
        jumpTableIndex++;
    }
    //Alkoholpegel Zeitabbau
    if (alcoholLevel > 0) {
        alcoholLevel = alcoholLevel - 1;
    }
    /* Cooldown weiterzählen
     * aktueller Stand: Werte nur interessant wenn > 0
     * darum keine if-Abfragen
     */
    immunityCooldown = immunityCooldown - 1;
    fireCooldown = fireCooldown - 1;
}
