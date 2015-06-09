#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "definitions.h"

class GameObject {

public:
    //Konstruktor und Destruktor
    GameObject(int posX, int posY, int length, int hight, consistencyType collusionType, objectType type);
    virtual ~GameObject();

    //Position()
    int getPosX() const;
    int getPosY() const;

    //Größe()
    int getLength() const;
    int getHeight() const;

    //Typen()
    objectType getType() const;
    consistencyType getCollisionType() const;

protected:
    //Position
    int posX;
    int posY;
    //Kollisionstyp
    consistencyType collisionType;

private:
    //Größe
    int length;
    int hight;
    //Objecttyp
    objectType type;

};

#endif // GAMEOBJECT_H
