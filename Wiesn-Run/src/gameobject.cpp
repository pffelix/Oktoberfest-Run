#include "gameobject.h"

GameObject::GameObject(int posX, int posY, int length, int height, consistencyType collusionType, objectType type) {
    this->posX = posX;
    this->posY = posY;
    this->length = length;
    this->height = height;
    this->collisionType = collusionType;
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

consistencyType GameObject::getCollisionType() const {
    return collisionType;
}
