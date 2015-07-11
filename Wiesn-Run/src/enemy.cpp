#include "enemy.h"

/// Class Enemy
/// lastUpdate:  update() 10.6 Johann

/**
 * @brief Konstruktor für ein Enemy-Objekt
 * @param posX      : X-Position
 * @param posY      : Y-Position
 * @param speedX    : Geschwindigkeit in X-Richtung
 *
 * @todo Skalieren der Werte und fireCooldown erhöhen
 */
Enemy::Enemy(int posX, int posY, int speedX, objectType enemy) : MovingObject(posX, posY, enemy, speedX, -maxSpeedY) {
   //Unterscheiden der verschiedenen Gegnerarten
    switch (enemy) {
    case BOSS: {
        health = 5;
        fireRate = frameRate;
        fireCooldown = 3 * frameRate;
        break;
    }
    case enemy_tourist: {
        health = 1;
        fireRate = 2 * frameRate;
        fireCooldown = 3 * frameRate;
        break;
    }
    case enemy_security: {
        health = 1;
        //bedeutet der Gegner kann nicht schießen
        fireCooldown = -1;
        break;
    }
    default: {
        qDebug("Fehler beim Anlegen des Gegners: Default-Case");
        break;
    }

    }
    death = false;
    inflictedDamage = 1;
    DeathCooldown = frameRate;

    /*
    //Grafik - Enemy wird initialisiert
    setPixmap(QPixmap(":/images/images/enemy.png"));
    setPos(getPosX() - 0.5*getLength(), yOffset - getPosY() - getHeight());
    */
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

bool Enemy::receiveDamage(int damage) {
    health = health - damage;
    death = !(health > 0);
    if (death) {
        setSpeedX(0);
    }
    return death;
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
 * @brief Enemy::getFireCooldown
 * @return fireCooldown
 */
int Enemy::getFireCooldown() const{
    return fireCooldown;
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
 * @brief Enemy::getDeathCooldown
 * @return deathCooldown
 */
int Enemy::getDeathCooldown() const {
    return DeathCooldown;
}

/**
 * @brief Enemy::update
 * führt Bewegungen des Gegners aus
 */
void Enemy::update() {
    if (death) {
        DeathCooldown = DeathCooldown - 1;
    } else {
        //Bewegung durchführen
        updatePosition();

        if (fireCooldown == 0) {
            fireCooldown = fireRate;
        } else if (fireCooldown > 0){
            fireCooldown = fireCooldown - 1;
        }
    }

    /* Bewegung durchführen
     *      ist außerhalb dem IF-statement weil der Gegner noch fallen soll, wenn er in der Luft stirbt.
     */
    updatePosition();
}
