#include "player.h"

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

int Player::getImmunityCooldown() {
    return immunityCooldown;
}

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
