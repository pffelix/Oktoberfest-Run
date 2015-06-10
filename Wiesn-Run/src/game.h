#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QSortedList>
#include <QMultiHash>
#include "gameobject.h"
#include "input.h"

enum collisionType {
    obstacleCollision, enemyCollision, powerupCollision
};

enum collisionDirection {
    fromLeft, fromRight, fromAbove, fromBelow
};

struct eventStruct {
    GameObject objectA;
    GameObject objectB;
    enum collisionType collision;
    enum collisionDirection direction;
};

struct scoreStruct {
    int enemiesKilled;
    int distanceCovered;
    int alcoholPoints;
};

class Game {
public:
    Game();
    ~Game();

    /// Startet das Spiel, wird einmalig von main() aufgerufen
    void startGame();

    QList<struct eventStruct> eventsToHandle;
    QMultiHash states;

private:
    int getStepSize();
    void appendWorldObjects();
    void reduceWorldObjects();
    void evaluateInput();
    void calculateMovement();
    void detectCollision();
    void correctMovement();
    void handleEvents();
    void renderGraphics();
    void playSound();
    void endGame();

    QSortedList<GameObject> worldObjects;
    QSortedList<GameObject> levelInitial;
    QSortedList<GameObject> levelSpawn;
    struct scoreStruct score;
    int stepSize;
    GameObject *playerObjPointer;
    Input keyInputs;
};

#endif // GAME_H
