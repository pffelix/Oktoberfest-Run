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
    audioID = 0;

    switch (type) {
    case obstacle: {
        // Verhältnis 1:2 (b:h)
        this->length = playerScale * (3.0 / 2.0);
        this->height = playerScale * 2;

        //Grafik - Obstacle Images initialisieren
        setPixmap(QPixmap(":/images/images/obstacle.png"));
        setPos(getPosX() - 0.5*getLength(), yOffset - getPosY() - getHeight());
        qDebug("   Obstacle erstellt");
        break;
    }
    case plane: {
        // Verhältnis 2:(1/3)
        this->length = playerScale * 2;
        this->height = playerScale / 3;

        // Grafik - Plane Images initialisieren
        setPixmap(QPixmap(":/images/images/plane.png"));
        setPos(getPosX() - getLength()*0.5, yOffset - getPosY() - getHeight());
        qDebug("   Plane erstellt");
        break;
    }
    case player: {
        // Verhältnis 1:2 (b:h)
        this->length = playerScale;
        this->height = playerScale * 2;

        //Grafik - Player wird initialisiert
        setPixmap(QPixmap(":/images/images/player1.png"));
        setPos(getPosX() - 0.5*getLength(), yOffset - getPosY() - getHeight());
        qDebug("   Player erstellt");
        break;
    }
    case enemy_tourist: {
        // Verhältnis 1:2 (b:h)
        this->length = playerScale;
        this->height = playerScale * 2;

        //Grafik - Enemy wird initialisiert
        setPixmap(QPixmap(":/images/images/tourist1.png"));
        setPos(getPosX() - 0.5*getLength(), yOffset - getPosY() - getHeight());
        qDebug("   Tourist erstellt");
        break;
    }
    case enemy_security: {
        // Verhältnis 1:2
        this->length = playerScale;
        this->height = playerScale * 2;

        setPixmap(QPixmap(":/images/images/security.png"));
        setPos(getPosX() - 0.5*getLength(), yOffset - getPosY() - getHeight());
        qDebug("   Security erstellt");
        break;

    }
    case powerUp: {
        // Verhältnis (2/3):(2/3)
        this->length = playerScale * (2.0 / 3.0);
        this->height = this->length;

        //Grafik - powerup Grafik initialisieren
        setPixmap(QPixmap(":/images/images/hendl.png"));
        setPos(getPosX() - getLength()*0.5, yOffset - getPosY() - getHeight());
        qDebug("   PowerUp erstellt");
        break;
    }
    case shot: {
        // Verhältnis (1/3):(2/3) (b:h)
        this->length = playerScale * (1.0 / 3.0);
        this->height = playerScale * (2.0 / 3.0);

        //Grafik - Attackgrafik initialisieren
        setPixmap(QPixmap(":/images/images/attack.png"));
        setPos(getPosX() - getLength()*0.5, yOffset - getPosY() - getHeight());
        qDebug("   Shot erstellt");
        break;
    }
    case BOSS: {
        this->length = 2 * playerScale;
        this->length = 4 * playerScale;

        setPixmap(QPixmap(":/images/images/boss.png"));
        setPos(getPosX() - getLength()*0.5, yOffset - getPosY() - getHeight());
        qDebug("   Boss erstellt");
        break;
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

void GameObject::setAudioID(int audioID) {
    this->audioID = audioID;
}

int GameObject::getAudioID() const {
    return audioID;
}
