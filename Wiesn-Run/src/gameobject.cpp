#include "gameobject.h"

/**
 * @brief GameObject::GameObject
 * Konstruktor
 * @param length    : Länge
 * @param height    : Höhe
 * @param type      : Typ
 * @param posX      : X-Position
 * @param posY      : Y-Position
 * @param colType   : Kollisionstyp
 *
 * @author Johann
 */
GameObject::GameObject(int posX, int posY, int length, int height, objectType type) {
    this->posX = posX;
    this->posY = posY;
    this->length = length;
    this->height = height;
    this->type = type;
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
