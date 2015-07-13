#include "player.h"

/// Class Player
/// lastUpdate: update() 10.6 Johann

Player::Player(int posX, int posY, int speedX) : MovingObject(posX, posY, player, speedX, -maxSpeedY) {
    health = 3;
    //Startpegel 5 alle 5 Sekunden wird eins abgebaut
    alcoholLevel = 5 * (5 * frameRate);
    jumpState = false;
    speedScale = 1;
    ammunation = 5;
    inflictedDamage = 1;
    immunityCooldown = 0;
    fireRate =  frameRate / 2;
    fireCooldown = 0;

    enemiesKilled = 0;
    alcoholDamageCooldown = 0;
}

Player::~Player() {

}

int Player::getHealth() const{
    return health;
}

/**
 * @brief Player::setHealth
 * Leben wird erhöht
 *
 * @param health
 * Wert, um den das Leben erhöht wird
 */
void Player::setHealth(int health) {
    this->health = health;
}
void Player::increaseHealth(int health) {
    this->health = this->health + health;
    if (this->health > maxHealth) {
        this->health = maxHealth;
    }
}

/**
 * @brief Player::receiveDamage
 * Dem Spieler wird schaden zugefügt, falls er nicht immun ist.
 *
 * @return true, wenn der Spieler tot ist.
 * @author Johann
 */
bool Player::receiveDamage(int damage) {
    if (immunityCooldown == 0) {
        health = health - damage;
        immunityCooldown = frameRate;
    }
    return !(health > 0);
}

int Player::getAlcoholLevel() const {
    return alcoholLevel;
}

/**
 * @brief Player::increaseAlcoholLevel
 * AlkoholPegel wird verändert. Durch einen negativen Wert im Argument wird der Pegel gesenkt
 *
 * @param additionalAlcohol
 * Wert um den erhöht wird
 */
void Player::increaseAlcoholLevel(int additionalAlcohol) {
    // Erhöhe bzw. Senke den Alkoholstand, verhindere jedoch, dass er unter Null fällt
    if ((alcoholLevel + additionalAlcohol) <= 0) {
        alcoholLevel = 0;
    } else {
        alcoholLevel = alcoholLevel + (additionalAlcohol);
    }

}

/**
 * @brief Player::decreaseAlcoholLevel
 * verringert den Pegel des Spielers
 * @todo Überflüssig, da nie aufgerufen. Auch wenn der Name es nicht vermuten lässt: increaseAlcoholLevel kann den Level auch verringern und wird benutzt.
 *
 * @param decreaseLevel
 * Wert um den der Pegel verringert wird
 *
 */
 void Player::decreaseAlcoholLevel(int decreaseLevel) {
    alcoholLevel = alcoholLevel - decreaseLevel;
    if (alcoholLevel < 0 ) {
        alcoholLevel = 0;
    }
}

int Player::getAmmunatiuon() const {
    return ammunation;
}

void Player::increaseAmmunation(int ammunationBonus) {
    ammunation = ammunation + ammunationBonus;
}

void Player::decreaseAmmunation() {
    ammunation = ammunation - 1;
}

void Player::setFireCooldown() {
    fireCooldown = fireRate;
}

int Player::getFireCooldown() {
    return fireCooldown;
}

int Player::getInflictedDamage() const {
    return inflictedDamage;
}

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
        jumpCooldown = 2 * frameRate / 3;
        setSpeedY(maxSpeedY);
    }
}

bool Player::inJump() const{
    return jumpState;
}

void Player::resetJumpState() {
    jumpState = false;
}

void Player::abortJump() {
    setSpeedY(-maxSpeedY);
}

int Player::getEnemiesKilled() {
    return enemiesKilled;
}

void Player::increaseEnemiesKilled() {
    enemiesKilled = enemiesKilled + 1;
}

int Player::getSpeedScale() const {
    return speedScale;
}

/**
 * @brief Player::update
 * Die updatePosition-Methode des Spielers wird aufgerufen.
 * Falls sich der Spieler im Sprung befindet die verbeibende Zeit der Aufwärtsbewegung um 1 verringern.
 * Abklingzeiten für den Alkoholpegel, für Schadensimmunität und fürs Feuern verringern.
 * Schaden zufügen, falls der Spieler zuviel Alkohol im Blut hat
 *
 * @author Johann
 */
void Player::update() {
    //Bewegung ausführen
    updatePosition();

    //Sprungverlauf
    if (jumpState) {
        if (jumpCooldown > 1) {
            //verbleibende Sprungdauer verringern
            jumpCooldown = jumpCooldown - 1;
        } else {
            //Sprung wird zu Fall
            setSpeedY(-maxSpeedY * speedScale);
        }
    }
    if (getPosY() > 0) {
        jumpState = true;
    } else {
        jumpState = false;
    }

    //Zeitlicher Abbau von Cooldowns
    if (alcoholLevel > 0) {
        alcoholLevel = alcoholLevel - (minusAlcoholPerSecond / frameRate);
    }
    if (immunityCooldown > 0) {
        immunityCooldown = immunityCooldown - 1;
    }
    if (fireCooldown > 0) {
        fireCooldown = fireCooldown - 1;
    }

    //Skalierung der Geschwindigkeit des Spielers bei geringem Leben
    if (health < 2) {
        speedScale = 2;
    } else {
        speedScale = 1;
    }

    //Schaden bei zu hohem Alkoholpegel
    if (alcoholLevel > maxAlcohol) {
        if (alcoholDamageCooldown == 0) {
            health = health - 1;
            alcoholDamageCooldown = 4 * frameRate;
        } else {
            alcoholDamageCooldown = alcoholDamageCooldown - 1;
        }
    } else {
        alcoholDamageCooldown = 0;
    }
}
