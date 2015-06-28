#include "player.h"

/// Class Player
/// lastUpdate: update() 10.6 Johann

Player::Player(int posX, int posY, int speedX) : MovingObject(posX, posY, player, speedX, -maxSpeedY) {
    health = 3;
    //Startpegel 5 alle 5 Sekunden wird eins abgebaut
    alcoholLevel = 5 * (5 * frameRate);
    jumpState = false;
    ammunation = 5;
    inflictedDamage = 1;
    immunityCooldown = 0;
    fireRate = 1 * frameRate;
    fireCooldown = 0;

    enemiesKilled = 0;
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
 * @brief Player::receiveDamage
 * @return Lebenszustand des Spielers: true = tot
 */
bool Player::receiveDamage(int damage) {
    if (!(immunityCooldown > 0)) {
        health = health - damage;
        immunityCooldown = frameRate;
    }
    return !(health > 0);
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
 * @brief Player::getInflictedDamage
 * @return Schaden den der Spieler zufügt
 */
int Player::getInflictedDamage() const {
    return inflictedDamage;
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
void Player::setImmunityCooldown(int remainingTime) {
    if (immunityCooldown < remainingTime) {
        immunityCooldown = (remainingTime * frameRate);
    }
}

/**
 * @brief beginnt einen Sprung
 * Nur wenn der Spieler sich nicht in der Luft befindet
 */
void Player::startJump() {
    //
    if (!(jumpState)) {
        jumpState = true;
        jumpCooldown = frameRate;
        setSpeedY(maxSpeedY);
    }
}

/**
 * @brief gibt den Sprung-Zustande des Spielers zurück
 * @return
 */
bool Player::inJump() const{
    return jumpState;
}

/**
 * @brief Gibt an dass der Spieler nicht in einem Sprung ist
 */
void Player::resetJumpState() {
    jumpState = false;
}
/**
 * @brief Methode wird aufgerufen, wenn der Spieler bei einem Sprung mit einem Hinderniss zusammengestoßen ist
 */
void Player::abortJump() {
    setSpeedY(-maxSpeedY);
}

/**
 * @brief Player::getEnemiesKilled
 * Übergibt die Zahl getöteter Gegner
 */
int Player::getEnemiesKilled() {
    return enemiesKilled;
}

/**
 * @brief Perhöht die Anzahl der getöteten Gegner um 1
 */
void Player::increaseEnemiesKilled() {
    enemiesKilled = enemiesKilled + 1;
}

/**
 * @brief Player::update
 * führt die Bewegung des Spielers aus (über updatePosition) und verringert Cooldown-Variable
 * @author Johann
 */
void Player::update() {
    //Bewegung ausführen
    updatePosition();

    if (jumpState) {
        if (jumpCooldown > 1) {
            jumpCooldown = jumpCooldown - 1;
        } else {
            setSpeedY(-maxSpeedY);
        }
    }
    if (getPosY() > 0) {
        jumpState = true;
    } else {
        jumpState = false;
    }

    //Alkoholpegel Zeitabbau
    if (alcoholLevel > 0) {
        alcoholLevel = alcoholLevel - 1;
    }
    /* Cooldowns weiterzählen
     * aktueller Stand: Werte nur interessant wenn > 0
     * darum keine if-Abfragen
     */
    immunityCooldown = immunityCooldown - 1;
    fireCooldown = fireCooldown - 1;
}
