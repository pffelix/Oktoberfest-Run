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

/**
 * @brief GameObject Konstruktor
 * Jedes Objekt bekommt ihr seine Grafik zugewiesen und die "Startposition" wird in Scenenkoordinaten errechnet
 * @param posX      : X-Position
 * @param posY      : Y-Position
 * @param type      : Typ
 *
 * @author Johann, Flo
 */
GameObject::GameObject(int posX, int posY, objectType type) {
    this->posX = posX;
    this->posY = posY;
    this->type = type;
    audioID = 0;

    //Grafik Initialisierungen aller Objekte außer Powerups
    switch (type) {
    case obstacle: {
        // Verhältnis (3/2):2 (b:h)
        length = playerScale * (3.0 / 2.0);
        height = playerScale * 2;

        //Grafik - Obstacle Images initialisieren
        setPixmap(QPixmap(":/images/images/barrel.png"));
        setPos(posX - length*0.5, yOffset - posY - height - 7);
        qDebug("   Obstacle erstellt");
        break;
    }
    case plane: {
        // Verhältnis 2:(1/3)
        length = playerScale * 2;
        height = playerScale / 3;

        // Grafik - Plane Images initialisieren
        setPixmap(QPixmap(":/images/images/plane.png"));
        setPos(posX - length*0.5, yOffset - posY - height);
        qDebug("   Plane erstellt");
        break;
    }
    case player: {
        // Verhältnis 1:2 (b:h)
        length = playerScale;
        height = playerScale * 2;

        //Grafik - Player wird initialisiert
        setPixmap(QPixmap(":/images/images/player1.png"));
        setPos(posX - 0.5*length, yOffset - posY - height);
        qDebug("   Player erstellt");
        break;
    }
    case enemy_tourist: {
        // Verhältnis (3/2):2 (b:h)
        length = playerScale * (3.0 /2.0);
        height = playerScale * 2;

        //Grafik - Enemy_tourist wird initialisiert
        setPixmap(QPixmap(":/images/images/tourist1.png"));
        setPos(posX - 0.5*length, yOffset - posY - height);
        qDebug("   Tourist erstellt");
        break;
    }
    case enemy_security: {
        // Verhältnis 1:2
        length = playerScale;
        height = playerScale * 2;

        //Grafik - Enemy_security wird initialisiert
        setPixmap(QPixmap(":/images/images/security.png"));
        setPos(posX - 0.5*length, yOffset - posY - height);
        qDebug("   Security erstellt");
        break;

    }
    case powerUp: {
        // Verhältnis (2/3):(2/3)
        length = playerScale * (2.0 / 3.0);
        height = length;

        //Powerups Grafiken werden im powerup Konstruktor erstellt da sie nicht im ObjectType enum aufgenommen sind
        setPos(posX - length*0.5, yOffset - posY - height);
        break;
    }
    case shot: {
        // Verhältnis (1/3):(2/3) (b:h)
        this->length = playerScale * (1.0 / 3.0);
        this->height = playerScale * (2.0 / 3.0);

        //Grafik - Attackgrafik initialisieren
        setPixmap(QPixmap(":/images/images/beer.png"));
        setPos(posX - length*0.5, yOffset - posY - height);
        qDebug("   Shot erstellt");
        break;
    }
    case BOSS: {
        this->length = 3 * playerScale;
        this->height = 4 * playerScale;

        //Grafik - Bossgrafik initialisieren
        setPixmap(QPixmap(":/images/images/boss.png"));
        setPos(posX - length*0.5 -10, yOffset - posY - height);
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
