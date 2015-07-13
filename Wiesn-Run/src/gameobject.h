#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "definitions.h"
#include <QGraphicsPixmapItem>

/**
 * @brief Das Spieler-Objekt.
 * Dieses Objekt repräsentiert das Grundobjekt. Das Objekt beschreibt ein einfaches Rechteck, mit den Attributen:
 *  - X/Y-Position
 *  - Länge/Höhe
 *  - Objekt-Typ
 *  - Audio-ID
 *
 * @author Johann, Flo
 */
class GameObject : public QGraphicsPixmapItem {

public:

    // ------------ Konstruktor, Destruktor ----------------

    GameObject(int posX, int posY, int length, int height, objectType type);
    GameObject(int posX, int posY, objectType type);
    virtual ~GameObject();

    // ------------ Öffentliche Methoden -------------------

    // -------Position-------
    int getPosX() const;                // Gibt die X-Position des Objekts zurück
    int getPosY() const;                // Gibt die Y-Position des Objekts zurück

    // -------Abmessungen-------
    int getLength() const;              // Gibt die Länge des Objekts zurück
    int getHeight() const;              // Gibt die Breite des Objekts zurück

    // -------Objekt-Typ-------
    objectType getType() const;         // Gibt den Objekt.Typ des Objekts zurück

    // -------Audio-ID-------
    void setAudioID(int audioID);       // Setzt eine Audio-ID fest
    int getAudioID() const;             // Gibt die Audio-ID zurück

protected:
    // X-Position
    int posX;
    // Y-Position
    int posY;

private:
    //Länge
    int length;
    // Höhe
    int height;
    //Objekt-Typ
    objectType type;
    // Audio-ID
    int audioID;

};

#endif // GAMEOBJECT_H
