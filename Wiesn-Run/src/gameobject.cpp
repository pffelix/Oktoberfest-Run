#include "gameobject.h"

GameObject::GameObject(int posX, int posY, int length, int hight, consistencyType collusionType, objectType type) {
    this->posX = posX;
    this->posY = posY;
    this->length = length;
    this->hight = hight;
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
