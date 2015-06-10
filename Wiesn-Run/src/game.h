#ifndef GAME_H
#define GAME_H


#include <list>

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

struct stateStruct {
    int a; // noch zu erstellen
};

bool operator<(GameObject const & lhs, GameObject & rhs) {
    return lhs.getPosX() < rhs.getPosX();
}



class Game {
public:
    Game();
    ~Game();

    std::list<struct eventStruct> eventsToHandle;
    //QMultiHash<struct stateStruct> states;

private:
    void startGame();
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

    std::list<GameObject> worldObjects;
    std::list<GameObject> levelInitial;
    std::list<GameObject> levelSpawn;
    struct scoreStruct score;
    int stepSize;
    GameObject *playerObjPointer;
    Input keyInputs;
};

#endif // GAME_H
