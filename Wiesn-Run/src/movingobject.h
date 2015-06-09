#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "gameobject.h"

class MovingObject : public GameObject{
public:
    MovingObject();
    virtual ~MovingObject();
    void setPosX(int posX);
    void setPosY(int posY);
    int getSpeedX() const;
    int getSpeedY() const;
    void setSpeedX(int speedX);
    void setSpeedY(int speedY);
    virtual void update();

protected:
    void updatePosition();

private:
    int speedX;
    int speedY;

};

#endif // MOVINGOBJECT_H
