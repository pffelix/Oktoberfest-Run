#ifndef SHOOT_H
#define SHOOT_H

#include "movingobject.h"

class Shoot :public MovingObject {

public:
    //Konstruktor und Destruktor
    Shoot(posX);
    ~Shoot();

    //Damage()
    int getInflictedDamage() const;

    //update()
    virtual void update();

private:
    int inflictedDamage;

};

#endif // SHOOT_H
