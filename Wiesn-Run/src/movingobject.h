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

    //Wir benötigt um Richtungsänderungen festzustellen
    void setDirLastFrame(bool dirLastFrame);
    bool getDirLastFrame();

    //'Abstrakte Methode' update
    virtual void update()=0;

    //spiegelt Grafiken
    void flipHorizontal();

protected:
    //Positionsupdate
    void updatePosition();

private:
    //Geschwindigkeit
    int speedX;
    int speedY;

    //Richtungsänderung im letzten Frame
    bool dirLastFrame;

};

#endif // MOVINGOBJECT_H
