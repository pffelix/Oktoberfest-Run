#ifndef PLAYER_H
#define PLAYER_H

#include "movingobject.h"

class Player : public MovingObject {

public:
    //Konstruktoren und Destruktoren
    Player(int posX, int posY, int speedX);
    ~Player();

    //Leben()
    int getHealth() const;
    void setHealth(int health); /// Nur PowerUp
    bool receiveDamage(int damage);

    //Alcoholpegel()
    int getAlcoholLevel() const;    /// Wird nicht benutzt 23.6
    void increaseAlcoholLevel(int additionalAlcohol);   /// Schlechte Bezeichnung
    bool decreaseAlcoholLevel(int decreaseLevel);       /// Schlechte Bezeichnung

    //Munnition()
    int getAmmunatiuon() const;     /// Wird nicht benutzt 23.6 bei implementierung Input(schießen)
    void increaseAmmunation(int ammunationBonus);   /// Schlechte Bezeichnung
    void decreaseAmmunation();      /// Schlechte Bezeichnung

    //Schadensimunität()
    int getImmunityCooldown() const;    /// Wird nicht benutzt 23.6
    void setImmunityCooldown(int remainingTime);

    //Sprung()
    void startJump();
    bool inJump() const;
    void resetJumpState();
    void abortJump();

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
    bool jumpState;
    //In-der-Luft-'Ort'
    int jumpCooldown;

};

#endif // PLAYER_H
