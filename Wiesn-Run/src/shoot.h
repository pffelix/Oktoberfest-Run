#ifndef SHOOT_H
#define SHOOT_H

#include "movingobject.h"

class Shoot : public MovingObject {

public:
    //Konstruktor und Destruktor
    Shoot(int posX, int posY, int length, int height, objectType type, collisionType colType, int speedX, int speedY);
    ~Shoot();

    //Damage()
    int getInflictedDamage() const;

    //update()
    virtual void update();

private:
    int inflictedDamage;

};

#endif // SHOOT_H
