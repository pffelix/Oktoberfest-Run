#ifndef ENEMY_H
#define ENEMY_H

#include "movingobject.h"

/**
 * @brief Das Gegner Objekt.
 * Dieses Objekt repräsentiert den Gegner. Das Objekt erbt von MovingObjekt und die wichtigsten Funktionen sind:
 *  - Automatische Aktualisierung
 *  - Schaden erhalten
 * die wichtigsten Attribute sind:
 *  - Leben
 *  - Schaden
 * Die Gegner-Objekte führen alle Bewegungen selbstständig aus nur das Bierkrugwerfen wird von außen geregelt.
 *
 * @author Johann
 */
class Enemy : public MovingObject {

public:

    // ------------ Konstruktor, Destruktor ----------------

    Enemy(int posX, int posY, int speedX, objectType enemy);
    ~Enemy();

    // ------------ Öffentliche Methoden -------------------

    // -------Leben-------
    int getHealth() const;              // Gibt Leben des Gegners zurück
    void setHealth(int health);         // Setzt das Leben des Gegners auf den übergebenen Wert
    bool receiveDamage(int damage);     // Fügt dem Gegner schaden zu, falls möglich

    // -------Feuern-------
    int getInflictedDamage() const;     // Gibt den Schaden zurück, den der Gegner zufügt
    int getFireCooldown() const;        // Gibt verbleibende Nachladezeit zurück

    // -------Tod-------
    bool getDeath() const;              // Gibt den Todeszustand des Gegners zurück
    void setDeath(bool death);          // setz den Todeszustand des Gegners
    int getDeathCooldown() const;       // Gibt die verbleibende Zeit an, die der Gegner noch angezeigt werden soll, wenn er tot ist

    // -------update-------
    virtual void update();              // Automatische Aktualisierung

private:
    // Leben
    int health;
    // Feuergeschwindigkeit
    int fireRate;
    // verbleibende Nachladezeit
    int fireCooldown;
    // Schaden
    int inflictedDamage;
    // Todeszustand
    bool death;
    // verbleibende Zeit nach Tod
    int DeathCooldown;
};

#endif // ENEMY_H
