#include "player.h"

///Klasse Player

Player::Player() {
}

int Player::getHealth() const{
    return health;
}

void Player::setHealth(int health) {
    this->health = health;
}

int Player::getAlcoholLevel() const {
    return alcoholLevel;
}

/*
 * keine gute Lösung
 */
void Player::increaseAlcoholLevel(int additionalAlcohol) {
    alcoholLevel = alcoholLevel - additionalAlcohol;
}

void Player::decreaseAlcoholLevel() {

}

int Player::getAmmunatiuon() const {
    return ammunation;
}

void Player::increaseAmmunation() {
    ammunation = ammunation + 1;
}

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

void Player::setJump(bool jump) {
    jumpActive = jump;
}

void Player::setFall() {
    jumpActive = true;
    jumpTableindex = fallIndex;
}

void Player::resetJump() {
    jumpActive = false;
    jumpTableindex = 0;
}

/**
 * @brief Player::update
 * führt die Bewegung des Spielers aus und verringert Cooldown-Variablen
 */
void Player::update() {
    //Bewegung ausführen
    posX = posX + speedX;
    if (jumpActive) {
        posY = posY + jumpTable[jumpTableindex];
        jumpTableindex = jumpTableindex + 1;
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
