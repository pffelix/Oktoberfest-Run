#include "gameobject.h"

GameObject::GameObject(int posX, int posY, int length, int height, collisionType colType, objectType type) {
    this->posX = posX;
    this->posY = posY;
    this->length = length;
    this->height = height;
    this->collisionType = colType;
    this->type = type;
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
