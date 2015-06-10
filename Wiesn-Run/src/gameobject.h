#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "definitions.h"

class GameObject {

public:
    //Konstruktor und Destruktor
    GameObject(int posX, int posY, int length, int height, objectType type, collisionType colType);
    ~GameObject();

    //Position()
    int getPosX() const;
    int getPosY() const;

    //Größe()
    int getLength() const;
    int getHeight() const;

    //Typen()
    objectType getType() const;
    collisionType getCollisionType() const;

protected:
    //Position
    int posX;
    int posY;
    //Kollisionstyp
    collisionType colType;

private:
    //Größe
    int length;
    int height;
    //Objecttyp
    objectType type;

};

#endif // GAMEOBJECT_H
