#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "definitions.h"
#include <QGraphicsPixmapItem>

class GameObject : public QGraphicsPixmapItem {

public:
    //Konstruktor und Destruktor
    GameObject(int posX, int posY, int length, int height, objectType type, collisionType colType);
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
    collisionType colType;

private:
    //Objecttyp
    objectType type;
    //Größe
    int length;
    int height;

};

#endif // GAMEOBJECT_H
