#include "gameobject.h"

/**
 * @brief Konstruktor für ein GameObject.
 * Die Attribute Länge, Höhe und Objekt-Typ können nicht mehr geändert werden und X/Y-Position nur durhc erbende Klassen.
 *
 * @param posX X-Position
 * @param posY Y-Position
 * @param length Länge
 * @param height Breite
 * @param type Objekt-Typ
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
 * Je nach Objekt-Typ bekommt hier jedes Objekt Abmessungen und eine Grafik zugewiesen und die "Startposition" wird in Scenenkoordinaten errechnet.
 * Die Attribute Länge, Höhe und Objekt-Typ können nicht mehr geändert werden und X/Y-Position nur durhc erbende Klassen.
 *
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
        if(rand()%2 == 0) {
            setPixmap(QPixmap(":/images/images/barrel.png"));
            setPos(posX - length*0.5, yOffset - posY - height - 7);
        }
        else {
            setPixmap(QPixmap(":/images/images/kasten.png"));
            setPos(posX - length*0.5, yOffset - posY - height);
        }
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

/**
 * @brief Destruktor
 */
GameObject::~GameObject() {

}

/**
 * @brief Gibt die X-Position des Objekts zurück.
 *
 * @return int
 */
int GameObject::getPosX() const {
    return posX;
}

/**
 * @brief Gibt die Y-Position des Objekts zurück.
 *
 * @return int
 */
int GameObject::getPosY() const {
    return posY;
}

/**
 * @brief Gibt die Länge des Objekts zurück.
 *
 * @return int
 */
int GameObject::getLength() const {
    return length;
}

/**
 * @brief Gibt die Höhe des Objekts zurück.
 *
 * @return int
 */
int GameObject::getHeight() const {
    return height;
}

/**
 * @brief Gibt den Objekt-Typ des Objekts zurück.
 *
 * @return objectType
 */
objectType GameObject::getType() const	{
    return type;
}

/**
 * @brief Setzt die Audio-ID fest. Diese wird in der game.cpp benötigt, um objektspezifische Sounds wiederzugeben.
 *
 * @param audioID Audio-ID
 */
void GameObject::setAudioID(int audioID) {
    this->audioID = audioID;
}

/**
 * @brief Gibt die Audio-ID des Objekts zurück.
 *
 * @return int
 */
int GameObject::getAudioID() const {
    return audioID;
}
