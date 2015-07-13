#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "gameobject.h"

/**
 * @brief Das Moving-Object.
 * Hierbei handelt es sich um eine abstrakte Klasse, die nicht instanziert werden kann. Die Klasse erbt von GameObject.
 * Die wichtigsten Funktionen sind:
 *  - Bewegungsausführung
 *  - Graphik
 *
 * @author Simon, Rupert, Johann, Flo
 */
class MovingObject : public GameObject {

public:

    // ------------ Konstruktor, Destruktor ----------------

    MovingObject(int posX, int posY, objectType type, int speedX, int speedY);
    ~MovingObject();

    //Position()
    void setPosX(int posX);
    void setPosY(int posY);

    // ------------ Öffentliche Methoden -------------------

    // -------Geschwindigkeit-------
    int getSpeedX() const;
    int getSpeedY() const;
    void setSpeedX(int speedX);
    void setSpeedY(int speedY);


    // -------'Abstrakte Methode' update-------
    virtual void update()=0;

    // -------Graphik-------
    void updateFramesDirection();   // aktualisiert die Framezahl die ohne Unterbrechung in eine Richtung gelaufen wurde
    void flipHorizontal();          // spiegelt Grafiken
    void swapImage();               // wechselt Grafiken um Animation zu erzeugen


protected:
    // -------Positionsupdate-------
    void updatePosition();          // Bewegungsausführung


private:
    // Horizontalgeschwindigkeit
    int speedX;
    // Vertikalgeschwindigkeit
    int speedY;

    //gibt an für wieviele Frames ohne Unterbrechung in einer Richtung gelaufen wurde
    int framesDirection = 0;
    //merkt sich welches Bild gerade gesetzt ist (für Bewegungsanimation)
    bool imageState = true;

};

#endif // MOVINGOBJECT_H
