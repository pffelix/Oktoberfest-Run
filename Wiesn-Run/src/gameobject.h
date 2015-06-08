#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "definitions.h"

class GameObject {

public:
    GameObject(int posX, int posY, int length, int hight, consistencyType collusionType, objectType type);
    ~GameObject();

    int getPosX() const;
    int getPosY() const;
    int getLength() const;
    int getHeight() const;
    objectType getType() const;
    consistencyType getCollisionType() const;

protected:
    int posX;
    int posY;
    consistencyType collisionType;

private:
    int length;
    int hight;
    objectType type;

};

#endif // GAMEOBJECT_H
