#include "enemy.h"

/// Class Enemy
/// lastUpdate:  update() 10.6 Johann


Enemy::Enemy(int posX, int posY, int length, int height, objectType type, collisionType colType, int speedX, int speedY) : MovingObject(posX, posY, length, height, type, colType, speedX, speedY) {
    health = 50;
    fireCooldown = 0;
    inflictedDamage = 10;
    death = false;
    DeathCooldown = 20;
}

Enemy::~Enemy() {

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
int Enemy::getInflictedDamage() const {
    return inflictedDamage;
}

/**
 * @brief Enemy::getDeath
 * Gibt an ob der Gegner Tot ist
 *
 * @return : Zustand - TOT
 */
bool Enemy::getDeath() const {
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
void Enemy::update() {
    if (death) {
        DeathCooldown = DeathCooldown - 1;
        if (DeathCooldown == 0) {
// Event: delete Enemy
        }
    } else {
        //Bewegung durchführen
        //posX = posX + this->getSpeedX();
        updatePosition();
        //Feuern
        if (fireCooldown == 0) {
//Event: create Shoot
            fireCooldown = fireRate;
        } else {
            fireCooldown = fireCooldown - 1;
        }
    }
}
