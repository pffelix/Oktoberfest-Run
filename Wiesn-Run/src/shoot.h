#ifndef SHOOT_H
#define SHOOT_H

#include "movingobject.h"

/**
 * @brief Das Schuss Objekt.
 * Dieses Objekt repräsentiert einen geworfenen Bierkrug. Das Objekt erbt von MovingObjekt und die wichtigsten Funktionen sind:
 *  - Automatische Aktualisierung
 * die wichtigsten Attribute sind:
 *  - Ursprung
 *  - Schaden
 * Die Bierkrüge führen alle Bewegungen selbständig aus
 *
 * @author Johann, Simon
 */
class Shoot : public MovingObject {

public:

    // ------------ Konstruktor, Destruktor ----------------

    Shoot(int posX, int posY, int direction, objectType origin);
    ~Shoot();


    // ------------ Öffentliche Methoden -------------------

    // -------Schaden-------
    int getInflictedDamage() const;     // Gibt den Schaden zurück, den der Bierkrug verursacht

    // -------Ursprung-------
    objectType getOrigin();             // Gibt zurück, wer den Bierkrug geworfen hat

    // -------Löschen-------
    bool getHarming() const;            // Gibt zurück, ob der Bierkrug noch Schaden zufügt
    void setToDelete();                 // Setzt, dass der Bierkrug keinen Schaden mehr zufügt

    // -------update-------
    virtual void update();              // Automatische Aktualisierung


private:
    // Schaden
    int inflictedDamage;
    // Ursprung Spieler oder Gegner
    objectType origin;
    // fügt Schaden zu?
    bool harming;

};

#endif // SHOOT_H
