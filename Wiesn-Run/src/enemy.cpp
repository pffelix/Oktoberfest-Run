#include "enemy.h"

/**
 * @brief Konstruktor für ein Enemy-Objekt
 * Erzeugt einen neuen Gegner, dabei werden Startwerte für die einzelnen Attribute festgelegt, je nachdem, um welchen Gegner es sich handelt.
 * Mögliche Gegnertypen: BOSS, Tourist, Security
 * Attribute in denen sich die Gegner unterscheiden: Leben, Feuerrate
 *
 * @param posX X-Position
 * @param posY Y-Position
 * @param speedX Geschwindigkeit in X-Richtung
 * @param enemy Gegnertyp
 *
 * @author Johann, Simon
 */
Enemy::Enemy(int posX, int posY, int speedX, objectType enemy) : MovingObject(posX, posY, enemy, speedX, -maxSpeedY) {
   //Unterscheiden der verschiedenen Gegnerarten
    switch (enemy) {
    case BOSS: {
        health = 5;
        fireRate = frameRate;
        fireCooldown = 2 * frameRate;
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
}

/**
 * @brief Destruktor
 */
Enemy::~Enemy() {

}

/**
 * @brief Gibt Leben des Gegners zurück.
 *
 * @return int
 */
int Enemy::getHealth() const {
    return health;
}

/**
 * @brief Setzt das Leben des Gegners.
 *
 * @param Wert, auf den das Leben gesetzt werden soll
 */
void Enemy::setHealth(int health) {
    this->health = health;
}

/**
 * @brief Fügt dem Gegner Schaden zu. Und gibt zurück, ob der Gegner danach tot ist.
 *
 * @param Wert des Schadens, der zugefügt werden soll
 * @return true, wenn der Gegner tot ist
 */
bool Enemy::receiveDamage(int damage) {
    health = health - damage;
    death = !(health > 0);
    if (death) {
        setSpeedX(0);
    }
    return death;
}

/**
 * @brief Gibt den Schaden zurück, den der Gegner zufügt.
 *
 * @return int
 */
int Enemy::getInflictedDamage() const {
    return inflictedDamage;
}

/**
 * @brief Gibt fir verbleibende Nachladezeit zurück.
 *
 * @return int
 */
int Enemy::getFireCooldown() const{
    return fireCooldown;
}

/**
 * @brief gibt den Todeszustand des Gegners zurück
 *
 * @return true, wenn der Gegner tot ist
 */
bool Enemy::getDeath() const {
    return death;
}

/**
 * @brief setzt den Todeszustand des Gegners
 *
 * @param Todeszustand
 */
void Enemy::setDeath(bool death) {
    this->death = death;
}

/**
 * @brief Gibt die verbleibende Zeit zurück, die der Gegner noch angezeigt werden soll.
 *      In Frames
 *
 * @return int
 */
int Enemy::getDeathCooldown() const {
    return DeathCooldown;
}

/**
 * @brief Hier werden alle framespezifischen Aktualisierungen durchgeführt.
 *
 * @author Johann
 */
void Enemy::update() {
    if (death) {
        /// Wenn der Gegner tot ist, wird die verbleibende Zeit der Anzeige um 1 verringert,
        DeathCooldown = DeathCooldown - 1;
    } else {
        /// sonst wird jedesmal, wenn die Nachladezeit abgelaufen ist, mit einem Bierkrug geworfen
        if (fireCooldown == 0) {
            fireCooldown = fireRate;
        } else if (fireCooldown > 0){
            fireCooldown = fireCooldown - 1;
        }
    }

    /// zuletzt wird die Position des Gegners aktualisiert, damit im Falle des Todes die Gegner nach unten Fallen.
    updatePosition();
}
