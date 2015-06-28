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
    int getAlcoholLevel() const;    /// Nötig für Score-Berechnung
    void increaseAlcoholLevel(int additionalAlcohol);   /// Schlechte Bezeichnung
    bool decreaseAlcoholLevel(int decreaseLevel);       /// Schlechte Bezeichnung

    //Munnition()
    int getAmmunatiuon() const;     /// Wird nicht benutzt 23.6 bei implementierung Input(schießen)
    void increaseAmmunation(int ammunationBonus);   /// Schlechte Bezeichnung
    void decreaseAmmunation();      /// Schlechte Bezeichnung

    //Schaden()
    int getInflictedDamage() const;

    //Schadensimunität()
    int getImmunityCooldown() const;    /// Wird nicht benutzt 23.6
    void setImmunityCooldown(int remainingTime);

    //Sprung()
    void startJump();
    bool inJump() const;
    void resetJumpState();
    void abortJump();

    // Getötete Gegner
    int getEnemiesKilled();
    void increaseEnemiesKilled();

    //update()
    virtual void update();

private:
    //Lebensstand
    int health;
    //Alkoholpegel
    int alcoholLevel;
    //verbleibende Munition
    int ammunation;
    //Schaden den der Spieler verursacht
    int inflictedDamage;
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
    // Getötete Gegner
    int enemiesKilled;

};

#endif // PLAYER_H
