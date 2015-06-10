#include "gameobject.h"


// Simon: GameObject::GameObject(int posX, int posY, int length, int height, collisionType colType, objectType type) {

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
>>>>>>> update
    this->posX = posX;
    this->posY = posY;
}
*/

GameObject::GameObject(int length, int height, objectType type, int posX, int posY, collisionType colType) {
    this->length = length;
    this->height = height;
    this->type = type;
    this->posX = posX;
    this->posY = posY;
    this->collisionType = colType;
}

int GameObject::getPosX() const {
    return posX;
}

int GameObject::getPosY() const {
    return posY;
}

int GameObject::getLength() const {
    return length;
}

int GameObject::getHeight() const {
    return height;
}

objectType GameObject::getType() const	{
    return type;
}

collisionType GameObject::getCollisionType() const {
    return collisionType;
}
