#include "gameobject.h"

/**
 * @brief GameObject::GameObject
 * Konstruktor
 * @param length
 * @param height
 * @param type
 * @param posX
 * @param posY
 * @param colType
 */
GameObject::GameObject(int posX, int posY, int length, int height, objectType type, collisionType colType) {
    this->posX = posX;
    this->posY = posY;
    this->length = length;
    this->height = height;
    this->type = type;
    this->colType = colType;
}
GameObject::~GameObject() {

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
    return colType;
}

bool GameObject::compGameObjects(const GameObject &objA, const GameObject &objB) {
    return objA.getPosX() < objB.getPosX();
}
