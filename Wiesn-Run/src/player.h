#ifndef PLAYER_H
#define PLAYER_H

#include "movingobject.h"

/**
 * @brief Das Spieler-Objekt.
 * Dieses Objekt repräsentiert den Spieler. Das Objekt erbt von MovingObject und die wichtigsten Funktionen sind:
 *  - Automatische Aktualisierung
 *  - Schaden erhalten
 *  - Springen
 * des weiteren sind die wichtigsten Attribute:
 *  - Leben
 *  - Alkoholpegel
 *  - Munition
 *  - Schaden
 * Die Bewegungen des Spielers über die Eingabe erfolgt in der step()-Methode der game.cpp. Es werden hierbei nur die Attribute speedx/y gesetzt.
 *
 * @author Johann
 */
class Player : public MovingObject {

public:

    // ------------ Konstruktor, Destruktor ----------------

    Player(int posX, int posY, int speedX);
    ~Player();

    // ------------ Öffentliche Methoden -------------------

    // -------Leben------
    int getHealth() const;              // Gibt Leben des Spielers zurück
    void setHealth(int health);         // Setzt das Leben des Spielers auf den übergebenen Wert
    void increaseHealth (int health);   // erhöht das Leben des Spielers um den Wert health
    bool receiveDamage(int damage);     // fügt dem Spieler Schaden, im Wert von damage, zu, falls möglich

    // ------Alcoholpegel------
    int getAlcoholLevel() const;
    void increaseAlcoholLevel(int additionalAlcohol);
    void decreaseAlcoholLevel(int decreaseLevel);

    // ------Munnition------
    int getAmmunatiuon() const;                     // Gibt Munition des Spielers zurück
    void increaseAmmunation(int ammunationBonus);   // Erhöht die Munition des Spielers um den Wert ammunationBonus
    void decreaseAmmunation();                      // Verringert die Munition des Spielers um 1

    // ------Schaden------
    int getInflictedDamage() const;     // Gibt den Schaden zurück, den der Spieler zufügt

    // ------Feuern------
    void setFireCooldown();         // Setzt die Nachladezeit auf eine Sekunde
    int getFireCooldown();          // Gibt die verbleibende Nachladezeit zurück

    // ------Schadensimunität------
    int getImmunityCooldown() const;                // Gibt die Vebleibende Zeit für Immunität zurück
    void setImmunityCooldown(int remainingTime);    // Setzt die Verbleibende Zeit für Immunität auf remainingTime fest

    // ------Sprung------
    void startJump();           // Beginnt einen Sprung des Spielers
    bool inJump() const;        // Gibt an, ob sich der Spieler in der Luft befindet
    void resetJumpState();      // Setzt den Wert, ob sich der Spieler in der Luft befindet auf false
    void abortJump();           // Bricht einen Sprung ab, und lässt den Spieler fallen

    // ------Getötete Gegner------
    int getEnemiesKilled();         // Gibt an wieviele Gegner der Spieler schon besiegt hat
    void increaseEnemiesKilled();   // Erhöht die Anzahl der besiegten Gegner um eins

    // ------Geschwindigkeitsskalierung------
    int getSpeedScale() const;      // Gibt den Skalierungsfaktor für die Geschwindigkeit zurück

    //update()
    virtual void update();      // Automatische Aktualisierung

private:
    // Leben
    int health;
    // Alkoholpegel
    int alcoholLevel;
    // Munition
    int ammunation;
    // Schaden, den der Spieler verursacht
    int inflictedDamage;
    // Nachladezeit
    int fireCooldown;
    // Feuergeschwindigkeit
    int fireRate;
    // Schadensimmunität (Unsterblichkeit)
    int immunityCooldown;
    // Sprungzustand
    bool jumpState;
    // Sprungdauer
    int jumpCooldown;
    // Skalierungsfaktor für Spielergeschwindigkeit
    int speedScale;
    // Wartezeit zwischen zwei Lebensabzügen wegen Alkoholüberdosis
    int alcoholDamageCooldown;
    // Anzahl getöteter Gegner
    int enemiesKilled;

};

#endif // PLAYER_H
