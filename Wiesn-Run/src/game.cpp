#include "game.h"
#include "movingobject.h"
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
 * @brief Erstelle QApplication app mit QGraphicsView Widget window (Eventfilter installiert) und Zeiger input auf Input Objekt.
 * Um Funktionen der Tastatur Eingabe entwickeln zu können ist ein Qt Widget Fenster nötig.
 * Auf dem Widget wird ein Eventfilter installiert welcher kontinuierlich Tastureingaben mitloggt.
 * Die Eingaben werden in dem Objekt der Input Klasse gespeichert und können über getKeyactions() abgerufen werden.
 *
 * Außerdem wird ein Timer gestartet, der in jedem Intervall timerEvent(...) aufruft, wo dann step() aufgerufen wird.
 * Das ist dann unsere Game-Loop. Der Timer funktioniert auch bei 5ms Intervall noch genau.
 *
 * Hier müssen auch die Sachen rein, die einmahlig beim Starten ausgeführt werden sollen
 * - alles laden, Fenster anzeigen
 * @return Rückgabewert von app.exec()
 * @author Felix, Rupert, Flo
 */
int Game::start() {
    // levelInitial laden
    // worldObjects = levelInitial
    makeTestWorld();
    // Player erstellen und in worldObjects einfügen

    // QGraphicsView Widget (Anzeigefenster) erstellen und einstellen
    QGraphicsView * window = new QGraphicsView();
    window->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->setFixedSize(800,600);
    window->setWindowTitle(QApplication::translate("Game Widget", "Game Widget (Input Test)"));
    window->show();
    qDebug("initialize window");

    //Timer installieren
    Input *keyInputs = new Input();
    window->installEventFilter(keyInputs);

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

        // Anfang, Ende, current nicht moving

        MovingObject *currentObject = dynamic_cast<MovingObject*>(*it);
        // Prüfen, ob das aktuelle Objekt überhaupt vom Typ MovingObject ist
        if (currentObject != 0) {

            GameObject *onePrevious = *(std::prev(it));
            GameObject *twoPrevious = *(std::prev(std::prev(it)));
            GameObject *oneAhead = *(std::next(it));
            GameObject *twoAhead = *(std::next(std::next(it)));
            GameObject *possibleCollision[] = {onePrevious, twoPrevious, oneAhead, twoAhead};


            for (int i = 0; i <= 3; i++) {

                int objASpeedX = currentObject->getSpeedX();
                int objASpeedY = currentObject->getSpeedY();

                bool movingRight;
                bool movingDown;
                int overlapX;
                int overlapY;

                int objBmaxX = possibleCollision[i]->getPosX() + (possibleCollision[i]->getLength() / 2);
                int objBminX = possibleCollision[i]->getPosX() - (possibleCollision[i]->getLength() / 2);
                int objBmaxY = possibleCollision[i]->getPosY() + (possibleCollision[i]->getHeight() / 2);
                int objBminY = possibleCollision[i]->getPosY() - (possibleCollision[i]->getHeight() / 2);
                int objAmaxX = currentObject->getPosX() + (currentObject->getLength() / 2);
                int objAminX = currentObject->getPosX() - (currentObject->getLength() / 2);
                int objAmaxY = currentObject->getPosY() + (currentObject->getHeight() / 2);
                int objAminY = currentObject->getPosY() - (currentObject->getHeight() / 2);

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

void Game::handleEvents() {

}

/**
 * @brief Game::handleCollisions
 *
 * @author Johann (15.6.15)
 */

void Game::handleCollisions() {

    collisionStruct handleEvent;
    int overlay;
    Enemy *handleEnemy;
    Shoot *handleShoot;

    //Liste mit den Events abarbeiten
    while (!eventsToHandle.empty()) {
        handleEvent = eventsToHandle.front();
        eventsToHandle.pop_front();

        switch (handleEvent.affectedObject->getType()) {

        case player: {
            /*Zussammenstöße des Spielers bearbeiten
             *  mit Wänden, Gegner, Schüssen, PowerUps
             *
             * PowerUps FEHLT!!!!!
             */
            switch (handleEvent.causingObject->getType()) {
            case obstacle: {
                /* Bewegung des Spielers muss abgebrochen und die Position richtiggestellt werden
                 *      4 Möglichkeiten: von oben, unten, links, rechts
                 */
                switch (handleEvent.direction) {
                case fromLeft: {
                    //Bewegung  in X-Richtungstoppen
                    playerObjPointer->setSpeedX(0);
                    //Überlappung berechnen und Spieler nach links versetzen
                    overlay = (playerObjPointer->getPosX() + playerObjPointer->getLength()) - handleEvent.causingObject->getPosX();
                    playerObjPointer->setPosX(playerObjPointer->getPosX() - overlay);
                    break;
                }
                case fromRight: {
                    //Bewegung in X-Richtung stoppen
                    playerObjPointer->setSpeedX(0);
                    //Überlappung berechnen und Spieler nach rechts versetzen
                    overlay = (handleEvent.causingObject->getPosX() + handleEvent.causingObject->getLength()) - playerObjPointer->getPosX();
                    playerObjPointer->setPosX(playerObjPointer->getPosX() + overlay);
                    break;
                }
                case fromAbove: {
                    //Bewegung in Y-Richtung stoppen, Sprung beenden!!
                    playerObjPointer->setSpeedY(0);
                    playerObjPointer->resetJump();
                    //Überlappung berechnen und Spieler nach obern versetzen
                    overlay = (handleEvent.causingObject->getPosY() + handleEvent.causingObject->getHeight()) - playerObjPointer->getPosY();
                    playerObjPointer->setPosY(playerObjPointer->getPosY() + overlay);
                    break;
                }
                case fromBelow: {
                    //Wegen Zusammenstoß wird ein Fall initiiert
                    playerObjPointer->setFall();
                    //Überlappung berechnen und Spieler nach obern versetzen
                    overlay = (playerObjPointer->getPosY() + playerObjPointer->getHeight()) - handleEvent.causingObject->getPosY();
                    playerObjPointer->setPosY(playerObjPointer->getPosY() + overlay);
                    break;
                }
                }

                break;
            }
            case enemy: {
                /* Zusammenstoß mit Gegener
                 *      2 Möglichkeiten:  Spieler kriegt Schaden, Gegner kriegt Schaden
                 *      Nur erster Fall!!!       für 2.Fall siehe affectedObject==enemy
                 */
                //Spieler bekommt Schaden, wenn der Zusammenstoß von links, rechts oder unten mit dem Gegner erfolgt
                if (!(handleEvent.direction == fromAbove)) {
                    handleEnemy = reinterpret_cast<Enemy*>(handleEvent.causingObject);
                    //Überprüfen ob der Spieler durch den zugefügten Schaden stirbt
                    if (hurtPlayer(handleEnemy->getInflictedDamage())) {
                        gameStats.gameOver = true;
                    }
                    handleEnemy = 0;
                }
            }
            case shot: {
                // Spieler kriegt Schaden, Bierkrug zum löschen vormerken
                handleShoot = reinterpret_cast<Shoot*>(handleEvent.causingObject);
                if (hurtPlayer(handleShoot->getInflictedDamage())) {
                    gameStats.gameOver = true;
                }
                shotsToDelete.push_back(handleShoot);
                handleShoot = 0;
                break;
            }
            case powerUp: {
                    // Spieler erhält Zusatzfähigkeit mit zeitlicher Beschränkung
                break;
            }
            }
            break;
        } // Ende: Case player

        case enemy: {
            /*Zussammenstöße des Gegners
             *  mit Wänden, Spieler, Schüssen
             *
             * Ignorieren: Gegner, PowerUps
             */
            handleEnemy = reinterpret_cast<Enemy*>(handleEvent.affectedObject);
            switch (handleEvent.causingObject->getType()) {
            case obstacle: {
                /* Bewegung des Gegners
                 *
                 */
                if (handleEvent.direction == fromAbove) {
                    //Gegner fällt auf Boden, Fall beendet
                    handleEnemy->setSpeedY(0);
                    overlay = (handleEvent.causingObject->getPosY() + handleEvent.causingObject->getHeight()) - handleEnemy->getPosY();
                    handleEnemy->setPosY(handleEnemy->getPosY() + overlay);
                } else {
                    // Gegner rennt gegen Wand, dreht um
                    handleEnemy->setSpeedX(-handleEnemy->getSpeedX());
                    if (handleEnemy->getSpeedX() > 0) {
                        //Gegner kommt von links
                        overlay = (handleEnemy->getPosX() + handleEnemy->getLength()) - handleEvent.causingObject->getPosX();
                        handleEnemy->setPosX(handleEnemy->getPosX() - overlay);
                    } else {
                        //Gegner kommt von rechts
                        overlay = (handleEvent.causingObject->getPosX() + handleEvent.causingObject->getLength()) - handleEnemy->getPosX();
                        handleEnemy->setPosX(handleEnemy->getPosX() + overlay);
                    }
                }
                break;
            }
            case shot: {
                break;
            }
            default: {

            }
            }
            break;
        }

        case shot: {
            break;
        }
        default: {
            //eigentlich unnötig
        }
        }
    }
}

/**
 * @brief Vergleichsoperand für die Sort-Methode der Listklasse.
 * Vergleicht die X-Positionen zweier Objekte.
 * @param first     : erstes Objekt
 * @param second    : zweites Objekt
 * @return true, wenn erstesObjekt weiter links
 */
bool Game::positionSort(GameObject *first, GameObject *second) {
    return (first->getPosX() < second->getPosX());
}

/**
 * @brief Fügt dem Spieler Schaden zu
 * @param Schaden
 * @return true Spieler ist gestorben
 */
bool Game::hurtPlayer(int damage) {
    playerObjPointer->setHealth(playerObjPointer->getHealth() - damage);
    return !(playerObjPointer->getHealth() > 0);

}
