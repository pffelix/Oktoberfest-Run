#ifndef GAME_H
#define GAME_H


#include <list>

#include "definitions.h"
#include "gameobject.h"
#include "input.h"

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
