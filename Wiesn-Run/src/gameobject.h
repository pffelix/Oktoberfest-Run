#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "definitions.h"

class GameObject {

public:
    //Konstruktor und Destruktor
    // SImon: GameObject(int posX, int posY, int length, int height, consistencyType collusionType, objectType type);
    //GameObject(int length, int hight, objectType type);
    //GameObject(int length, int hight, objectType type, int posX, int posY,);
    GameObject(int length, int height, objectType type, int posX, int posY, consistencyType collusionType);
    virtual ~GameObject();

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
    consistencyType collisionType;

private:
    //Größe
    int length;
    int height;
    //Objecttyp
    objectType type;

};

#endif // GAMEOBJECT_H
