#ifndef ENEMY_H
#define ENEMY_H

#include "movingobject.h"

class Enemy : public MovingObject {

public:

    //Konstruktor und Destruktor
    Enemy(int posX, int posY, int speedX, objectType enemy);
    ~Enemy();

    //Leben()
    int getHealth() const;
    void setHealth(int health);
    bool receiveDamage(int damage);

    //Damage()
    int getInflictedDamage() const;
    int getFireCooldown() const;

    //Tod()
    bool getDeath() const;
    void setDeath(bool death);
    int getDeathCooldown() const;

    //update()
    virtual void update();

private:
    //Lebensstand
    int health;
    //Feuergeschwindigkeit
    int fireRate;
    //verbleibende Nachladezeit
    int fireCooldown;
    //Schaden, den Gegner verursacht
    int inflictedDamage;
    //Todes-Zustand
    bool death;
    //verbleibende Zeit nach Tod
    int DeathCooldown;
};

#endif // ENEMY_H
