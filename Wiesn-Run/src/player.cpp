#include "player.h"

/**
 * @brief Konstruktor.
 * Erzeugt einen neuen Spieler.
 * Dabei werden Startwerte für alle Attribute festgelegt.
 *
 * @param posX X-Position im Level
 * @param posY Y-Position im Level
 * @param speedX HorizontalGeschwindigkeit
 *
 * @author Johann, Simon
 */
Player::Player(int posX, int posY, int speedX) : MovingObject(posX, posY, player, speedX, -maxSpeedY) {
    health = 3;
    alcoholLevel = 4 * (5 * frameRate);     // Startpegel 5 alle 5 Sekunden wird eins abgebaut
    jumpState = false;
    speedScale = 1;
    ammunation = 5;
    inflictedDamage = 1;
    immunityCooldown = 0;
    fireRate =  frameRate / 2;              // default-Wert für die Nachladezeit: 0.5 Sekunden
    fireCooldown = 0;

    enemiesKilled = 0;
    alcoholDamageCooldown = 0;
}

/**
 * @brief Destruktor.
 */
Player::~Player() {

}

/**
 * @brief Gibt Leben des Spielers zurück.
 *
 * @return int health
 */
int Player::getHealth() const{
    return health;
}

/**
 * @brief Leben wird erhöht.
 *
 * @param health
 * Wert, um den das Leben erhöht wird
 */
void Player::setHealth(int health) {
    if (health < 5) {
        this->health = health;
    } else {
        this->health = 5;
    }
}
void Player::increaseHealth(int health) {
    this->health = this->health + health;
    if (this->health > maxHealth) {
        this->health = maxHealth;
    }
}

/**
 * @brief Fügt dem Spieler Schaden zu, wenn er nicht immun ist, lässt ihn für eine Sekunde immun sein und gibt zurück, ob er gestorben ist.
 *
 * @param Schaden der dem Spieler zugefügt werden soll
 * @return true, wenn der Spieler gestorben ist
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
    alcoholLevel = alcoholLevel + additionalAlcohol;
    //Falls der alkohollevel unter Nullfällt wieder auf Null setzten
    if (alcoholLevel < 0) {
        alcoholLevel = 0;
    }

}

/**
  * @brief Verringert den Alkoholpegel des Spielers und den Wert decreaseLevel.
  * Falls der Wert unter 0 fällt wird er af 0 gesetzt
  *
  * @param Wert um den der Alkoholpegel verringert werden soll
  */
 void Player::decreaseAlcoholLevel(int decreaseLevel) {
    alcoholLevel = alcoholLevel - decreaseLevel;
    if (alcoholLevel < 0 ) {
        alcoholLevel = 0;
    }
}

 /**
 * @brief Gibt die Munition des Spielers zurück
 *
 * @return int
 */
int Player::getAmmunatiuon() const {
    return ammunation;
}

/**
 * @brief Erhöht die Munition des Spielers.
 *
 * @param Der Wert um den die Munition erhöht werden soll
 */
void Player::increaseAmmunation(int ammunationBonus) {
    ammunation = ammunation + ammunationBonus;
}

/**
 * @brief Verringert die Munition des Spielers um 1
 */
void Player::decreaseAmmunation() {
    ammunation = ammunation - 1;
}

/**
 * @brief Setzt die verbleibende Nachladezeit auf den default-Wert, fireRate.
 */
void Player::setFireCooldown() {
    fireCooldown = fireRate;
}

/**
 * @brief gibt die verbleibende Nachladezeit zurück.
 *
 * @return int
 */
int Player::getFireCooldown() {
    return fireCooldown;
}

/**
 * @brief Gibt den Schaden zurück, den der Spieler zufügt
 *
 * @return int
 */
int Player::getInflictedDamage() const {
    return inflictedDamage;
}

/**
 * @brief Gibt zurück, wie lange der Spieler noch Immun ist.
 *
 * @return int
 */
int Player::getImmunityCooldown() const {
    return immunityCooldown;
}

/**
 * @brief Zeit für Unverwundbarkeit wird gesetzt, in Frames
 *
 * @param Anzahl der Frames, für die der Spieler unverwundbar sein soll
 */
void Player::setImmunityCooldown(int remainingTime) {
    if (immunityCooldown < remainingTime) {
        immunityCooldown = (remainingTime * frameRate);
    }
}

/**
 * @brief Beginnt einen Sprung.
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

/**
 * @brief Gibt zurück, ob sich der Spieler in der Luft befindet.
 *
 * @return true, falls der Spieler in der Luft ist
 */
bool Player::inJump() const{
    return jumpState;
}

/**
 * @brief Setzt den Wert, dass sich der Spieler auf festem Grund befindet.
 */
void Player::resetJumpState() {
    jumpState = false;
}

/**
 * @brief bricht einen Sprung ab und initiert einen Fall.
 */
void Player::abortJump() {
    setSpeedY(-maxSpeedY * getSpeedScale());
}

/**
 * @brief Gibt zurück, wieviele Gegner der Spieler schon besiegt hat.
 *
 * @return int
 */
int Player::getEnemiesKilled() {
    return enemiesKilled;
}

/**
 * @brief Erhöht die Anzahl der besiegten Gegner um 1
 */
void Player::increaseEnemiesKilled() {
    enemiesKilled = enemiesKilled + 1;
}

/**
 * @brief Gibt den Skalierungsfaktor für die Spielergeschwindigkeit wieder.
 *
 * @return int
 */
int Player::getSpeedScale() const {
    return speedScale;
}

/**
 * @brief Hier werden alle framespezifischen Aktualisierungen durchgeführt.
 *
 * @author Johann
 */
void Player::update() {
    /// Bewegung ausführen
    updatePosition();

    /// Sprungverlauf:
    if (jumpState) {
        /// befindet sich der Spieler in der Luft und hat noch verbleibende Sprungdauer,
        /// so wird die verbleibende Sprungdauer um eins verringert, sonst wird ein Fall initiiert
        if (jumpCooldown > 1) {
            jumpCooldown = jumpCooldown - 1;
        } else {
            //Sprung wird zu Fall
            setSpeedY(-maxSpeedY * speedScale);
        }
    }
    /// Falls sich der Spieler über der Nullebene befindet, entspricht der Spieler ist in der Luft,
    /// wird jumpState auf true gesetzt, um einen Sprung zu verhindern
    if (getPosY() > 0) {
        jumpState = true;
    } else {
        jumpState = false;
    }

    // Zeitlicher Abbau von Cooldowns

    /// Alkoholpegel wird über die Zeit abgebaut
    if (alcoholLevel > 0) {
        alcoholLevel = alcoholLevel - (minusAlcoholPerSecond / frameRate);
    }
    /// Immunität wird über die Zeit abgebaut
    if (immunityCooldown > 0) {
        immunityCooldown = immunityCooldown - 1;
    }
    /// restliche Nachladezeit wird verkürzt
    if (fireCooldown > 0) {
        fireCooldown = fireCooldown - 1;
    }

    /// Der Skalierungsfaktor für die Spielergeschwindigkeit wird aktualisiert:
    ///  Spieler kann sich doppelt so schnell bewegen, wenn er nur noch ein Leben hat.
    if (health < 2) {
        speedScale = 2;
    } else {
        speedScale = 1;
    }

    /// Hat der Spieler zu viel Alkohol im Blut, so verliert er alle 4 Sekunden ein Leben.
    if (alcoholLevel > maxAlcohol) {
        //wenn der Alkoholpegel zu hoch wird dem Spieler alle 4 Sekunden ein Leben abgezogen
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
