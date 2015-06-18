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
#include <QGraphicsView>
#include <chrono>


/**
 * @brief Struktur für die Events
 * Enthält affectedObject als Objekt, aus dessen Sicht die Kollision berechnet wurde. affectedObject ist immer ein MovingObject,
 * causingObject kann beides sein.
 * Die Art und Richtung der Kollision werden mit gespeichert.
 * @author Simon, Johann(15.6)
 */
struct collisionStruct {
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
class Game : QObject {
    //Q_OBJECT
public:
    Game(int argc, char *argv[]);
    ~Game();

    /// Startet das die Game-Loop, wird einmalig von main() aufgerufen
    int step();
    /// Startet die Mockup QApplication app
    int run(QApplication& app);

    struct stateStruct gameStats;
    //Liste von Kollisionen
    std::list<struct collisionStruct> eventsToHandle;
    //QMultiHash<struct stateStruct> states;
    int start();

protected:
    void timerEvent(/*QTimerEvent *event*/);

private:
    int getStepSize();
    void appendWorldObjects();
    void reduceWorldObjects();
    void evaluateInput();
    void calculateMovement();
    void detectCollision(std::list<GameObject*> *objToCalculate);
    void correctMovement();
    void handleEvents();
    void handleCollisions();
    void renderGraphics();
    void playSound();
    void endGame();
    bool hurtPlayer(int damage);

    void makeTestWorld();

    // Enthält alle in der Welt befindlichen Objekte
    std::list<GameObject*> worldObjects;
    // Enthält alle statischen Objekte, die zu Anfang gespawnt werden
    std::list<GameObject*> levelInitial;
    // Enthält alle Objekte, die während des Spiels gespawnt werden
    std::list<GameObject*> levelSpawn;
    // Schüsse, die gelöscht werden müssen
    std::list<Shoot*> shotsToDelete;


    struct scoreStruct score;
    int stepSize;
    Player *playerObjPointer;

    /// Zeiger auf QApplication
    QApplication *appPointer;
    /// für Zeitmessung
    std::chrono::high_resolution_clock::time_point letzterAufruf;
};

#endif // GAME_H

