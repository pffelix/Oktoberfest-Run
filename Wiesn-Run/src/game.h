#ifndef GAME_H
#define GAME_H


#include <list>

#include "definitions.h"
#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "shoot.h"
#include "input.h"
#include <QApplication>
#include <QWidget>


//bool operator < (GameObject const & lhs, GameObject & rhs) {
//    return lhs.getPosX() < rhs.getPosX();
//}


/**
 * @brief Struktur für die Events
 * Enthält objectA als Objekt, aus dessen Sicht die Kollision berechnet wurde. objectA ist immer ein MovingObject,
 * objectB kann beides sein.
 * Die Art und Richtung der Kollision werden mit gespeichert.
 * @author Simon, Johann
 */
struct eventStruct {
    GameObject *affectedObject;
    GameObject *causingObject;
    enum collisionType collision;
    enum collisionDirection direction;
};

/**
 * @brief Game-Klasse
 * Die Game-Klasse bündelt alle Kern-Funktionalitäten des Spiels.
 * Innerhalb der main.cpp wird eine Instanz dieser Klasse angelegt,
 * aus der heraus das gesamte Spiel läuft.
 * Die einzelnen Methoden werden in der game.cpp jeweils erklärt.
 *
 * @lastChanges funtion handleCollisions hinzugefügt
 *
 * @author Simon, Johann
 */
class Game {
public:
    Game(int argc, char *argv[]);
    ~Game();

    /// Startet das die Game-Loop, wird einmalig von main() aufgerufen
    int exec();
    /// Startet die Mockup QApplication app
    int run(QApplication& app);

    std::list<struct eventStruct> eventsToHandle;
    //QMultiHash<struct stateStruct> states;


private:
    int getStepSize();
    void appendWorldObjects();
    void reduceWorldObjects();
    void evaluateInput();
    void calculateMovement();
    void detectCollision();
    void correctMovement();
    void handleEvents();
    void handleCollision();
    void renderGraphics();
    void playSound();
    void endGame();

    std::list<GameObject> worldObjects;
    std::list<GameObject> levelInitial;
    std::list<GameObject> levelSpawn;
    std::list<GameObject> deleteItems;
    bool positionSort(GameObject *first, GameObject *second);
    struct scoreStruct score;
    int stepSize;
    Player *playerObjPointer;


};

#endif // GAME_H
