#include "gameobject.h"

/*
GameObject::GameObject(int length, int hight, objectType type) {
    this->length = length;
    this->hight = hight;
    this->type = type;
}
*/
/*
GameObject::GameObject(int length, int hight, objectType type, int posX, int posY) {
    this->length = length;
    this->hight = hight;
    this->type = type;
    this->posX = posX;
    this->posY = posY;
}
*/

GameObject::GameObject(int length, int hight, objectType type, int posX, int posY, consistencyType collusionType) {
    this->length = length;
    this->hight = hight;
    this->type = type;
    this->posX = posX;
    this->posY = posY;
    this->collisionType = collusionType;
}

int GameObject::getPosX() const {
    return posX;
}

int GameObject::getPosY() const {
    return posY;
}

int GameObject::getLength() const {
    return lenght;
}

int GameObject::getHeight() const {
    return height;
}

int GameObject::getType() const	{
    return type;
}

int GameObject::getCollisionType() const {
    return collisionType;
}
