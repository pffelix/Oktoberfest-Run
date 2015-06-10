#include "enemy.h"

/// Class Enemy
/// lastUpdate:  update() 10.6 Johann


Enemy::Enemy() {
}

/**
 * @brief Enemy::getHealth
 * Gibt Lebensstand zurück
 *
 * @return : Lebensstand
 */
int Enemy::getHealth() const {
    return health;
}

/**
 * @brief Enemy::setHealth
 * Lebensstand wird gesetzt
 *
 * @param health : Lebensstand
 */
void Enemy::setHealth(int health) {
    this->health = health;
}

/**
 * @brief Enemy::getInflictedDamage
 * gibt Schaden zurück, den der gegner zufügt
 *
 * @return : Schaden
 */
int Enemy::getInflictedDamage() {
    return inflictedDamage;
}

/**
 * @brief Enemy::getDeath
 * Gibt an ob der Gegner Tot ist
 *
 * @return : Zustand - TOT
 */
bool Enemy::getDeath() {
    return death;
}

/**
 * @brief Enemy::setDeath
 * Zustand-TOT wird gesetzt
 *
 * @param death : Zustand-TOT
 */
void Enemy::setDeath(bool death) {
    this->death = death;
}

/**
 * @brief Enemy::update
 * führt Bewegungen des Gegners aus und lässt ihn schießen
 *      , falls er lebt!
 *
 * Hier werden zwei Events erzeugt:
 *  1) DeleteEnemy : wenn gegner Tot ist und seine erscheinungszeit abgelaufen ist
 *  2) CreateShot : wenn Gegner bereit zum Schießen ist
 */
virtual void Enemy::update() {
    if (death) {
        DeathCooldown = DeathCooldown - 1;
        if (DeathCooldown = 0) {
// Event: delete Enemy
        }
    } else {
        //Bewegung durchführen
        posX = posX + this->getSpeedX();
        //Feuern
        if (fireCooldown = 0) {
//Event: create Shoot
            fireCooldown = fireRate;
        } else {
            fireCooldown = fireCooldown - 1;
        }
    }
}
