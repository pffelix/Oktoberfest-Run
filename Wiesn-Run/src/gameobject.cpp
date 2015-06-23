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

GameObject::GameObject(int posX, int posY, objectType type) {
    this->posX = posX;
    this->posY = posY;
    this->type = type;

    switch (type) {
    case obstacle: {
        // Verhältnis 1:2 (b:h)
        this->length = playerScale;
        this->height = playerScale * 2;
    }
    case player: {
        // Verhältnis 1:2 (b:h)
    }
    case enemy: {
        // Verhältnis 1:2 (b:h)
        this->length = playerScale;
        this->height = playerScale * 2;
        break;
    }
    case powerUp: {
        // Verhältnis (2/3):(2/3)
        this->length = playerScale * (2 / 3);
        this->height = this->length;
        break;
    }
    case shot: {
        // Verhältnis (1/3):(2/3) (b:h)
        this->length = playerScale * (1/3);
        this->height = playerScale * (2/3);
        break;
    }
    case BOSS:{
/// BOSS definieren (Flo wegen Bild/Abmessungen fragen)
    }
    };
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
