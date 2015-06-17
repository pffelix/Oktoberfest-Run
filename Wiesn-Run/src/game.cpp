#include "game.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <iomanip>
#include <cmath>

#include "player.h"
#include "gameobject.h"
#include "enemy.h"
#include "shoot.h"

/**
 * @brief Konstruktor
 * Initialisiert den appPointer
 * @param argc
 * @param argv
 * @author Rupert
 */
Game::Game(int argc, char *argv[]) : QObject() {
    /// Initialisiert den appPointer mit der QApplication
    appPointer = new QApplication(argc,argv);
}

Game::~Game() {

}

/**
 * @brief wird regelmäßig aufgerufen
 * @param event
 * @author Rupert
 */
void Game::timerEvent(QTimerEvent *event)
{
    step();
    ///@TODO return von step...
}

/**
 * @brief Erstelle QApplication app mit Widget inputwindow (Eventfilter installiert) und Zeiger input auf Input Objekt.
 * Um Funktionen der Tastatur Eingabe entwickeln zu können ist ein Qt Widget Fenster nötig.
 * Auf dem Widget wird ein Eventfilter installiert welcher kontinuierlich Tastureingaben mitloggt.
 * Die Eingaben werden in dem Objekt der Input Klasse gespeichert und können über getKeyactions() abgerufen werden.
 *
 * Außerdem wird ein Timer gestartet, der in jedem Intervall timerEvent(...) aufruft, wo dann step() aufgerufen wirt.
 * Das ist dann unsere Game-Loop. Der Timer funktioniert auch bei 5ms Intervall noch genau.
 *
 * Hier müssen auch die Sachen rein, die einmahlig beim Starten ausgeführt werden sollen
 * - alles laden, Fenster anzeigen
 * @return Rückgabewert von app.exec()
 * @author Felix, Rupert
 */
int Game::start() {
    // levelInitial laden
    // worldObjects = levelInitial
    makeTestWorld();
    // Player erstellen und in worldObjects einfügen

    QWidget inputwindow;
    inputwindow.resize(320, 240);
    inputwindow.show();
    inputwindow.setWindowTitle(QApplication::translate("Game Widget", "Game Widget (Input Test)"));
    qDebug("initialize inputwindow");
    Input *input = new Input();
    inputwindow.installEventFilter(input);

    qDebug("Starte Timer mit 500msec-Intervall");
    Game::startTimer(500);

    return appPointer->exec();
}

/**
 * @brief Game-Loop
 * Diese Funktion wird von timerEvent() aufgerufen und ist für den kompletten Ablauf des Spiels verantwortlich.
 * grober Ablauf:
 * LOOP:
 *  - Timer starten
 *  - Neue Objekte zur Welt hinzufügen
 *  - alte Objekte löschen
 *  - Input auslesesn
 *  - Bewegungen berechnen
 *  - Kollisionskontrolle
 *  - Bewegungen korrigieren
 *  - Events behandeln (Treffer..)
 *  - Grafik rendern und ausgeben
 *  - Sound ausgeben
 *  - verbleibende Zeit im Slot berechnen (Timer auslesen)
 *  - entsprechend warten
 * goto LOOP
 * @return 0 bei fehlerfreiem Beenden
 * @author Rupert
 */
int Game::step() {
    using namespace std::chrono;

    /// Zeit seit dem letzten Aufruf ausrechnen und ausgeben
    high_resolution_clock::time_point akt = letzterAufruf;
    letzterAufruf = high_resolution_clock::now();
    std::size_t ms = duration_cast<milliseconds>(letzterAufruf-akt).count();
    std::string msg = "Game::step() | Vergangene Zeit seit letztem step(): " + std::to_string(ms) + "ms";
    qDebug(msg.c_str());

//    appendWorldObjects();
//    reduceWorldObjects();
//    evaluateInput();
      calculateMovement();
//    detectCollision();
//    correctMovement();
//    handleEvents();
//    renderGraphics();
//    playSound();


    return 0;
}


/**
 * @brief Game::detectCollision
 * Diese Funktion berechnet die Kollisionen, welche zwischen ObjektA und ObjektB auftreten.
 * Die Kollision wird dabei immer aus Sicht von ObjektA berechnet. D.h. Variablen wie movingRight
 * bedeuten, dass ObjektA sich nach rechts bewegt hat und dabei ObejektB von Links getroffen hat.
 * @todo Auslesen und durchgehen der Liste, setzen der Variablen, Erstellen der Kollisionsevents
 * @author Simon
 */
void Game::detectCollision(std::list<GameObject*> &objToCalculate) {

    for (std::list<GameObject*>::iterator it=objToCalculate.begin(); it != objToCalculate.end(); ++it) {

        GameObject *currentObject = *it;
        GameObject *onePrevious = *(--it);
        GameObject *twoPrevious = *(--it);
        ++it;
        ++it;
        GameObject *oneAhead = *(++it);
        GameObject *twoAhead = *(++it);

        int objASpeedX;
        int objASpeedY;
        bool movingRight;
        bool movingDown;

        int overlapX;
        int overlapY;
        int objBmaxX;
        int objBminX;
        int objBmaxY;
        int objBminY;
        int objAmaxX;
        int objAminX;
        int objAmaxY;
        int objAminY;

        bool horizontalCollision = false;

        // Check whether collision happend from left
        if (objASpeedX > 0) {
            movingRight = true;
        } else {
            movingRight = false;
        }

        // Check whether collision happend from above
        if (objASpeedY < 0) {
            movingDown = true;
        } else {
            movingDown = false;
        }

        // Calculate overlap in the X coordinate
        if (movingRight == true) {
            overlapX = objAmaxX - objBminX;
        } else {
            overlapX = objBmaxX - objAminX;
        }

        // Calculate overlap in the Y coordinate
        if (movingDown == true) {
            overlapY = objBmaxY - objAminY;
        } else {
            overlapY = objAmaxY - objBminY;
        }

        // Detect dominant collision direction
        if (overlapX > overlapY) {
            horizontalCollision = true;
        } else {
            horizontalCollision = false;
        }

    }
}

/**
 * @brief Erstellt ein paar Test-Objekte in worldObjects
 * Was wird erstellt:
 * - Objekt1 mit v=0 an x=10,y=0
 * - Objekt2 mit v=0 an x=20,y=0
 * - ObjektPlayer mit v=1 an x=5,y=0
 * alle Objekte sind 4 breit und 5 hoch
 * @author Rupert
 */
void Game::makeTestWorld() {
    GameObject *object1 = new GameObject(10,0,4,5,obstacle,stopping);
    GameObject *object2 = new GameObject(20,0,4,5,obstacle,stopping);
    Player *objectPlayer = new Player(5,0,4,5,player,stopping,1,0);
    worldObjects.push_back(object1);
    worldObjects.push_back(object2);
    worldObjects.push_back(objectPlayer);

}

void Game::appendWorldObjects() {

}

void Game::reduceWorldObjects() {

}

void Game::evaluateInput() {

}

/**
 * @brief Geht die worldObjects durch und aktualisiert bei jedem die Position
 * wird momentan auch über Debug ausgegeben
 * @author Rupert
 */
void Game::calculateMovement() {
    using namespace std;               // für std::list
    list<GameObject*>::iterator it;     // Iterator erstellen
    /// Schleife startet beim ersten Element und geht bis zum letzen Element durch
    for(it = worldObjects.begin(); it != worldObjects.end(); ++it) {
        GameObject *aktObject = *it;

        string msg = "OBJECT Position: XPos=" + to_string(aktObject->getPosX());
        qDebug(msg.c_str());

        MovingObject *aktMovingObject = dynamic_cast<MovingObject*> (aktObject);    // Versuche GameObject in Moving Object umzuwandeln
        if(aktMovingObject != 0) {
            aktMovingObject->update();          // Wenn der cast klappt, rufe update() auf.
            qDebug("update() für letztes Objekt wird aufgerufen");
        }

    }
}

void Game::correctMovement() {

}

void Game::handleEvents() {

}

void Game::renderGraphics() {

}

void Game::playSound() {

}

void Game::endGame() {

}
