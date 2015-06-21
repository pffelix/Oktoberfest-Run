#ifndef POWERUP_H
#define POWERUP_H
#include "gameobject.h"

/**
 * @brief Klasse für Power-Ups
 *
 * @author Johann
 */
class PowerUp : public GameObject {


public:
    /*
     * Konstruktor und Destruktor
     */
    PowerUp(int posX, int posY, int length, int height, int healthBonus, int alcoholLevelBonus, int ammunationBonus, int immunityCooldownBonus);
    ~PowerUp();

    ///Get-Methoden für die Objekteigenschaften
    int getHealthBonus() const;
    int getAlcoholLevelBonus() const;
    int getAmmunationBonus() const;
    int getImmunityCooldownBonus() const;

private:
    // Bonus auf Leben
    int healthBonus;
    // Bonus auf Alkoholpegel
    int alcoholLevelBonus;
    // Bonus auf Immunität
    int ammunationBonus;
    // Bonus auf Immunität
    int immunityCooldownBonus;

};

#endif // POWERUP_H
