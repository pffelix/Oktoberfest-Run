#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "definitions.h"
#include <QGraphicsPixmapItem>

class GameObject : public QGraphicsPixmapItem {

public:
    //Konstruktor und Destruktor
    GameObject(int posX, int posY, int length, int height, objectType type);
    GameObject(int posX, int posY, objectType type);
    virtual ~GameObject();

    //Position()
    int getPosX() const;
    int getPosY() const;

    //Größe()
    int getLength() const;
    int getHeight() const;

    //Typen()
    objectType getType() const;

    void setAudioID(int audioID);
    int getAudioID() const;

protected:
    //Position
    int posX;
    int posY;

private:
    //Größe
    int length;
    int height;
    //Objecttyp
    objectType type;
    int audioID;

};

#endif // GAMEOBJECT_H
