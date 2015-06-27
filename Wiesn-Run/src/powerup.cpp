#include "powerup.h"

/**
 * @brief Konstruktor
 * @param posX
 * @param posY
 * @param length
 * @param height
 * @param healthBonus
 * @param alcoholLevelBonus
 * @param ammunationBonus
 * @param immunityCooldownBonus
 * @author Johann
 */
PowerUp::PowerUp(int posX, int posY, int healthBonus, int alcoholLevelBonus, int ammunationBonus, int immunityCooldownBonus) : GameObject(posX, posY, powerUp) {
    this->healthBonus = healthBonus;
    this->alcoholLevelBonus = alcoholLevelBonus;
    this->ammunationBonus = ammunationBonus;
    this->immunityCooldownBonus = immunityCooldownBonus;
   // powType = type;
}

/**
 * @brief Destruktor
 * @author Johann
 */
PowerUp::~PowerUp() {

}

/**
 * @brief Gibt den Bonus auf Alcohollevel zurück
 * @author Johann
 */
int PowerUp::getAlcoholLevelBonus() const {
    return alcoholLevelBonus;
}

/**
 * @brief Gibt den Bonus auf Munnition zurück
 * @author Johann
 */
int PowerUp::getAmmunationBonus() const {
    return ammunationBonus;
}

/**
 * @brief Gibt den Bonus auf Leben zurück
 * @author Johann
 */
int PowerUp::getHealthBonus() const {
    return healthBonus;
}

/**
 * @brief Gibt den Bonus auf Immunität zurück
 * @author Johann
 */
int PowerUp::getImmunityCooldownBonus() const {
    return immunityCooldownBonus;
}

