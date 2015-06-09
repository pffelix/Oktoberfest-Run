#ifndef PLAYER_H
#define PLAYER_H

#include "movingobject.h"

class Player : public MovingObject {

public:
    Player();
    virtual ~Player();

    //Leben()
    int getHealth() const;
    void setHealth(int health); //zugefügter Schaden muss über eine Funktion geregelt werden

    //Alcoholpegel()
    int getAlcoholLevel() const;
    void increaseAlcoholLevel(int additionalAlcohol);
    void decreaseAlcoholLevel();

    //Munnition()
    int getAmmunatiuon() const;
    void increaseAmmunation();
    void decreaseAmmunation();

    //Schadensimunität()
    int getImmunityCooldown() const;
    void setImmunityCooldown(int immunityCooldown);

    //Sprung()
    void setJump(bool jump);
    void setFall();
    void resetJump();

    //update()
    void update();

private:
    int health;
    int alcoholLevel;
    int ammunation;
    int immunityCooldown;
    int fireCooldown;
    int fireRate;
    bool jumpActive;
    int jumpTableindex;
    int jumpTable[];

    const int fallIndex = 20;

};

#endif // PLAYER_H
