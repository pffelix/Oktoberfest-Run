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
    void setHealth(int health);
    void increaseHealth (int health);
    bool receiveDamage(int damage);

    //Alcoholpegel()
    int getAlcoholLevel() const;
    void increaseAlcoholLevel(int additionalAlcohol);
    void decreaseAlcoholLevel(int decreaseLevel);

    //Munnition()
    int getAmmunatiuon() const;
    void increaseAmmunation(int ammunationBonus);
    void decreaseAmmunation();

    //Feuern
    void setFireCooldown();
    int getFireCooldown();

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

    // Geschwindigkeitsskalierung
    int getSpeedScale() const;

    //update()
    virtual void update();

private:
    // Leben
    int health;
    // Alkoholpegel
    int alcoholLevel;
    // verbleibende Munition
    int ammunation;
    // Schaden den der Spieler verursacht
    int inflictedDamage;
    // Anzahl Frames Schadensimmunität (Unsterblichkeit)
    int immunityCooldown;
    // verbleibende Nachladezeit
    int fireCooldown;
    // Feuergeschwindigkeit
    int fireRate;
    // In-der-Luft-Zustand
    bool jumpState;
    // In-der-Luft-'Ort'
    int jumpCooldown;
    // Getötete Gegner
    int enemiesKilled;
    // Skalierungsfaktor für Spielergeschwindigkeit
    int speedScale;

};

#endif // PLAYER_H
