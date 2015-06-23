#include "player.h"

/// Class Player
/// lastUpdate: update() 10.6 Johann

Player::Player(int posX, int posY, int speedX) : MovingObject(posX, posY, player, speedX, -5) {
    health = 3;
    //Startpegel 5 alle 5 Sekunden wird eins abgebaut
    alcoholLevel = 5 * (5 * frameRate);
    jumpActive = false;
    jumpTableIndex = 0;
    ammunation = 0;
    immunityCooldown = 0;
    fireRate = 1 * frameRate;
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
    alcoholLevel = alcoholLevel + (additionalAlcohol * frameRate);
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
    alcoholLevel = alcoholLevel - (decreaseLevel * frameRate);
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
void Player::increaseAmmunation(int ammunationBonus) {
    ammunation = ammunation + ammunationBonus;
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
    this->immunityCooldown = (immunityCooldown * frameRate);
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
    setSpeedY(-5);
}

/**
 * @brief Player::update
 * führt die Bewegung des Spielers aus (über updatePosition) und verringert Cooldown-Variable
 * @author Johann
 */
void Player::update() {
    if (jumpActive) {
        setSpeedY(jumpTable[jumpTableIndex]);
        jumpTableIndex++;
    }
    //Bewegung ausführen
    updatePosition();
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
