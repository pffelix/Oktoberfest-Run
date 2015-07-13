#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "gameobject.h"

class MovingObject : public GameObject {

public:
    //Konstruktor und Destruktor
    //MovingObject(int length, int hight, objectType type);
    //MovingObject(int length, int hight, objectType type, int posX, int posY);
    MovingObject(int posX, int posY, objectType type, int speedX, int speedY);
    ~MovingObject();

    //Position()
    void setPosX(int posX);
    void setPosY(int posY);

    //Geschwindigkeit()
    int getSpeedX() const;
    int getSpeedY() const;
    void setSpeedX(int speedX);
    void setSpeedY(int speedY);


    //'Abstrakte Methode' update
    virtual void update()=0;

    //aktualisiert die Framezahl die ohne Unterbrechung in eine Richtung gelaufen wurde
    void updateFramesDirection();

    //spiegelt Grafiken
    void flipHorizontal();

    //wechselt Grafiken um Animation zu erzeugen
    void swapImage();

protected:
    //Positionsupdate
    void updatePosition();

private:
    //Geschwindigkeit
    int speedX;
    int speedY;

    //gibt an für wieviele Frames ohne Unterbrechung in einer Richtung gelaufen wurde
    int framesDirection = 0;

    //merkt sich welches Bild gerade gesetzt ist (für Bewegungsanimation)
    bool imageState = true;

};

#endif // MOVINGOBJECT_H
