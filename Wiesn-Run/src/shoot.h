#ifndef SHOOT_H
#define SHOOT_H

#include "movingobject.h"

class Shoot : public MovingObject {

public:
    //Konstruktor und Destruktor
    Shoot(int posX, int posY, int speedX, objectType origin);
    ~Shoot();

    //Damage()
    int getInflictedDamage() const;

    //Ursprung
    objectType getOrigin();

    //update()
    virtual void update();

private:
    //Schaden den der Bierkrug zufügt
    int inflictedDamage;
    //Wer hat den Bierkrug geworfen? Spieler oder Gegner
    objectType origin;

};

#endif // SHOOT_H
