#ifndef PLAYER_H
#define PLAYER_H

#include "movingobject.h"

class Player : public MovingObject {

public:
    //Konstruktoren und Destruktoren
    Player(int posX, int posY, int length, int height, objectType type, int speedX);
    ~Player();

    //Leben()
    int getHealth() const;
    void setHealth(int health); //zugefügter Schaden muss über eine Funktion geregelt werden

    //Alcoholpegel()
    int getAlcoholLevel() const;
    void increaseAlcoholLevel(int additionalAlcohol);
    bool decreaseAlcoholLevel(int decreaseLevel);

    //Munnition()
    int getAmmunatiuon() const;
    void increaseAmmunation(int ammunationBonus);
    void decreaseAmmunation();

    //Schadensimunität()
    int getImmunityCooldown() const;
    void setImmunityCooldown(int immunityCooldown);

    //Sprung()
    void setJump(bool jump);
    void setFall();
    void resetJump();

    //update()
    virtual void update();

private:
    //Lebensstand
    int health;
    //Alkoholpegel
    int alcoholLevel;
    //verbleibende Munition
    int ammunation;
    //Anzahl Frames Schadensimmunität (Unsterblichkeit)
    int immunityCooldown;
    //verbleibende Nachladezeit
    int fireCooldown;
    //Feuergeschwindigkeit
    int fireRate;
    //In-der-Luft-Zustand
    bool jumpActive;
    //In-der-Luft-'Ort'
    int jumpTableIndex;
    //In-der-Luft-Geschwindigkeiten
    int jumpTable[100];

    const int fallIndex = 20;

};

#endif // PLAYER_H
