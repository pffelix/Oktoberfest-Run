#ifndef ENEMY_H
#define ENEMY_H

#include "movingobject.h"

class Enemy : public MovingObject {

public:

    //Konstruktor und Destruktor
    Enemy();
    ~Enemy();

    //Leben()
    int getHealth() const;
    void setHealth(int health);

    //Damage()
    int getInflictedDamage() const;

    //Tod()
    bool getDeath() const;
    void setDeath(bool death);

    //update()
    void update();

private:
    int health;
    const int fireRate;
    int fireCooldown;
    int inflictedDamage;
    bool death;
    int DeathCooldown;
};

#endif // ENEMY_H
