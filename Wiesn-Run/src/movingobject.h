#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "gameobject.h"

class MovingObject : public GameObject {

public:
    //Konstruktor und Destruktor
    //MovingObject(int length, int hight, objectType type);
    //MovingObject(int length, int hight, objectType type, int posX, int posY);
    MovingObject(int posX, int posY, int length, int height, objectType type, collisionType colType, int speedX, int speedY);
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

protected:
    //Positionsupdate
    void updatePosition();

private:
    //Geschwindigkeit
    int speedX;
    int speedY;

};

#endif // MOVINGOBJECT_H
