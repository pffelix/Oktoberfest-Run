#include "game.h"
#include "movingobject.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <iomanip>
#include <cmath>

#include <fstream>

#include "player.h"
#include "gameobject.h"
#include "enemy.h"
#include "shoot.h"
#include "menu.h"


/**
 * @brief Verglecht zwei GameObjects, bezüglich der X-Position
 * @param 1.Objekt
 * @param 2.Objekt
 * @return true, wenn 1.Objekt weiter links als 2.Objekt
 * @author Simon
 */
struct compareGameObjects {
    bool operator()(GameObject *objA, GameObject *objB) {
        return objA->getPosX() < objB->getPosX();
    }
};


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
 * event muss drinstehen, damit der Timer die Funktion aufruft
 * @param event
 * @author Rupert
 */
void Game::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event)        // Warnung unterdrücken
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
 * @author Felix, Rupert, Flo, Simon
 */
int Game::start() {
    qDebug("Game::start()");


    // Fundamentale stepSize setzen
    stepIntervall = 1000/frameRate;

    // Menüs erstellen
    menuStart = new Menu(new std::string("Wiesn-Run"));
    menuStart->addEntry("Spiel neustarten",menuId_StartGame);
    menuStart->addEntry("Spiel beenden", menuId_EndGame);

    menuEnd = new Menu(new std::string("Game Over"));
    menuEnd->addEntry("Weiterspielen",menuId_Resume);
    menuEnd->addEntry("Highscore anzeigen",menuId_Highscore);
    menuEnd->addEntry("Credits anzeigen",menuId_Credits);
    menuEnd->addEntry("zurück zum Anfang",menuId_GotoStartMenu);

    // QGraphicsView Widget (Anzeigefenster) erstellen und einstellen
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,100000,768);
    window = new QGraphicsView(scene);
    window->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->setFixedSize(1024,768);
    window->setWindowTitle(QApplication::translate("Game Widget", "Game Widget (Input Test)"));
    window->show();
    qDebug("initialize window");

    // Event Filter installieren
    window->installEventFilter(keyInput);

    startNewGame();

    // Timer installieren
    qDebug("Starte Timer mit 500msec-Intervall");
    Game::startTimer(stepIntervall);

    ///@TODO hier wird das Startmenü übersprungen
    state = gameIsRunning;

    return appPointer->exec();
}

/**
 * @brief Startet neues Spiel
 * lädt Leveldatei
 * füllt worldobjects
 */
void Game::startNewGame() {
    // alles alte leeren
    scene->clear();
    worldObjects.clear();

    // Level festlegen, der geladen werden soll
    QString fileSpecifier = ":/levelFiles/levelFiles/level1.txt";
    loadLevelFile(fileSpecifier);
    // Spieler hinzufügen
    worldObjects.push_back(playerObjPointer);
    //Grafik - Spieler der Scene hinzufügen und window auf ihn zentrieren
    scene->addItem(playerObjPointer);
    window->centerOn(playerObjPointer->getPosX(), 384);
    // Spawn-Distanz setzen
    spawnDistance = 1000;
    // Szenen-Breite setzen
    sceneWidth = 1000;

    // Zeiger auf Objekte aus levelInitial in worldObjects verlegen
    while (!(levelInitial.empty())) {
        GameObject *currentObject = *levelInitial.begin();
        worldObjects.push_back(currentObject);
        levelInitial.pop_front();
        //Grafik
        scene->addItem(currentObject);
    }
}

/**
 * @brief Game::endGame
 */
void Game::endGame() {

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
 *  - Audio ausgeben
 *  - verbleibende Zeit im Slot berechnen (Timer auslesen)
 *  - entsprechend warten
 * goto LOOP
 * @return 0 bei fehlerfreiem Beenden
 * @author Rupert
 */
int Game::step() {
    using namespace std::chrono;

    /// Zeit seit dem letzten Aufruf ausrechnen und ausgeben

    //high_resolution_clock::time_point akt = letzterAufruf;
    //letzterAufruf = high_resolution_clock::now();
    //qDebug("Game::step() | Vergangene Zeit seit letztem step(): %d ms", static_cast<int>(duration_cast<milliseconds>(letzterAufruf-akt).count()));

    switch(state) {
        case gameMenuEnd:
            menuEnd->display();
            // Enter?
            if(keyInput->getKeyactions().contains(Input::Keyaction::Enter)) {
                // Menüpunkt ausgewählt
                switch(menuEnd->getSelection()->id) {
                    case menuId_Resume:
                        // Weiterspielen
                        state = gameIsRunning;
                        break;
                    case menuId_Highscore:
                        // Highscore Fenster anzeigen
                        break;
                    case menuId_Credits:
                        // Credit Fenster anzeigen
                        break;
                    case menuId_GotoStartMenu:
                        // Startmenü anzeigen
                        state = gameMenuStart;
                        break;
                }
            }

            // Up || Down?
            if(keyInput->getKeyactions().contains(Input::Keyaction::Up)) {
                menuEnd->changeSelection(Menu::menuSelectionChange::up);
            }
            if(keyInput->getKeyactions().contains(Input::Keyaction::Down)) {
                menuEnd->changeSelection(Menu::menuSelectionChange::down);
            }

            // ESC? -> Weiterspielen
            if(keyInput->getKeyactions().contains(Input::Keyaction::Exit)) {
                state = gameIsRunning;
            }

            break;

        case gameMenuStart:
            menuStart->display();

            // Enter?
            if(keyInput->getKeyactions().contains(Input::Keyaction::Enter)) {
                // Menüpunkt ausgewählt
                switch(menuStart->getSelection()->id) {
                    case menuId_StartGame:
                        startNewGame();
                        state = gameIsRunning;
                        break;
                    case menuId_EndGame:
                        qDebug("Spiel wurde über menuStart beendet");
                        exit(0);
                        break;
                }
            }

            // Up || Down?
            if(keyInput->getKeyactions().contains(Input::Keyaction::Up)) {
                menuStart->changeSelection(Menu::menuSelectionChange::up);
            }
            if(keyInput->getKeyactions().contains(Input::Keyaction::Down)) {
                menuStart->changeSelection(Menu::menuSelectionChange::down);
            }

            break;
        case gameIsRunning:


            worldObjects.sort(compareGameObjects());
            qDebug("---Nächster Zeitschritt---");

            appendWorldObjects(playerObjPointer);
            reduceWorldObjects(playerObjPointer);
            evaluateInput();
            worldObjects.sort(compareGameObjects());
            calculateMovement();
            worldObjects.sort(compareGameObjects());
            detectCollision(&worldObjects);
            handleCollisions();

            //    correctMovement();
            //    handleEvents();
            renderGraphics(&worldObjects);
            /// Mockup: add audioStruct player_jump to audioevents list
            std::list <float> distance;
            distance.push_front(1);
            audioStruct player_jump{"player_jump", distance};
            audioevents.push_front(player_jump);
            distance.push_front(0.3);
            distance.push_front(0.2);
            audioStruct scene_enemy{"scene_enemy", distance};
            audioevents.push_front(scene_enemy);
            /// send filled audioevents list to AudioControl Object, which updates current Output Sounds
            audioOutput->update(&audioevents);
            /// delete List audioStruct elements in list and fill it in the next step again
            audioevents.clear();
            break;
    }

    stepCount++;
    return 0;
}

/**
 * @brief Game::appendWorldObjects
 * @param playerPointer
 * Diese Funktion fügt der Spielwelt dynamisch Gegner hinzu. In jedem Zeitschritt wird die sortierte Liste
 * levelSpawn vom Anfang her durchlaufen. Ist die Distanz des Spielers zum Gegner kleiner als die Distanz levelSpawn,
 * so wird das Objekt den worldObjects hinzugefügt und aus levelSpawn gelöscht. Die for-Schleife läuft solange, bis
 * das erste Mal ein Objekt weiter als levelSpawn vom Spieler entfernt ist. Dann wird abgebrochen, da alle folgenden
 * Objekte auf Grund der Sortierung noch weiter entfernt sein werden.
 * @author Simon
 */
void Game::appendWorldObjects(Player *playerPointer) {
    while (!(levelSpawn.empty())) {
        GameObject *currentObj = *levelSpawn.begin();
        if ( (currentObj->getPosX() - playerPointer->getPosX()) < spawnDistance ) {
            worldObjects.push_back(currentObj);
            levelSpawn.pop_front();
            //Grafik - Gegner de Scene hinzufügen
            scene->addItem(currentObj);
        } else {
            break;
        }
    }
}


/**
 * @brief Game::reduceWorldObjects
 * @param playerPointer
 * Die Funktion reduceWorldObjects löscht die Zeiger auf die GameObjects aus dem Spiel, von denen der Spieler bereits
 * weiter rechts als die spawnDistance entfernt ist.
 * Entfernt Bierkrüge, die im letzten Durchlauf mit Gegenständen kollidiert sind
 * @todo Objekte löschen anstatt nur die Zeiger aus der Liste entfernen
 * @author Simon, Johann
 */
void Game::reduceWorldObjects(Player *playerPointer) {

    while (!(worldObjects.empty())) {
        GameObject *currentObj = *worldObjects.begin();
        if ((playerPointer->getPosX() - currentObj->getPosX()) > spawnDistance) {
            worldObjects.pop_front();
            //Grafik - Objekte aus der Scene löschen
            scene->removeItem(currentObj);

            delete currentObj;
        } else {
            break;
        }
    }

    //Entferne die Bierkrüge die an Wände oder Gegner, etc. gestoßen sind.
    objectsToDelete.sort(compareGameObjects());
    while (!(objectsToDelete.empty())) {
        GameObject *currentObject= *objectsToDelete.begin();
        //use worldObjects.erase(position)
        std::list<GameObject*>::iterator it = worldObjects.begin();
        while((*it != currentObject) && (it != worldObjects.end())) {
            it++;
        }
        if (*it == currentObject) {
            worldObjects.erase(it);
            objectsToDelete.pop_front();

            //Grafik - Bierkrüge löschen
            scene->removeItem(currentObject);

            delete currentObject;
        }
    }
}

/**
 * @brief Checkt welche Tasten für die Spielkontrolle gedrückt sind
 * mögliche Tasten:
 *  - Pfeil rechts zum laufen
 *  - Pfeil hoch zum springen
 *  - Leertaste zum schießen
 *  - ESC für Menü
 * @author Rupert
 */
void Game::evaluateInput() {
    // Pfeil rechts?
    if(keyInput->getKeyactions().contains(Input::Keyaction::Right)) {
        playerObjPointer->setSpeedX(playerSpeed);
    } else {
        playerObjPointer->setSpeedX(0);
    }

    // Pfeil oben?
    if(keyInput->getKeyactions().contains(Input::Keyaction::Up)) {
        playerObjPointer->startJump();
    }

    // Leertaste?
    if(keyInput->getKeyactions().contains(Input::Keyaction::Shoot)) {
        //Shoot *playerFire = new Shoot(playerObjPointer->getPosX(),playerObjPointer->getPosY(),1,player);
        Shoot *playerFire = new Shoot(playerObjPointer->getPosX()+playerObjPointer->getLength()/2,playerObjPointer->getPosY(),1,player);
        worldObjects.push_back(playerFire);
        scene->addItem(playerFire);
    }

    // Menü bei ESC
    if(keyInput->getKeyactions().contains(Input::Keyaction::Exit)) {
        state = gameMenuEnd;
    }
}

/**
 * @brief Geht die worldObjects durch und aktualisiert bei jedem die Position,
 *      Gegner bei denen der DeathCooldown abgelaufen ist, werden zum loeschen vorgemerkt,
 *      Gegner bei denen der FireCooldownabgelaufen ist feuern.
 * wird momentan auch über Debug ausgegeben
 * @author Rupert, Johann
 */
void Game::calculateMovement() {
    using namespace std;               // für std::list

    /// für qDebug (Rupert)
    std::string objecttypes[] = {"Player", "Enemy ", "Obstac", "Shot  ", "PwrUp ", "BOSS  "};
    int speedX=0,speedY=0;

    list<GameObject*>::iterator it;     // Iterator erstellen
    /// Schleife startet beim ersten Element und geht bis zum letzen Element durch
    for(it = worldObjects.begin(); it != worldObjects.end(); ++it) {
        GameObject *aktObject = *it;
        MovingObject *aktMovingObject = dynamic_cast<MovingObject*> (aktObject);    // Versuche GameObject in Moving Object umzuwandeln
        if(aktMovingObject != 0) {
            aktMovingObject->update();          // Wenn der cast klappt, rufe update() auf.
            //falls es sich um einen Gegner handelt feuern
            if (aktMovingObject->getType() == enemy){
                Enemy *aktEnemy = dynamic_cast<Enemy*> (aktMovingObject);
                if (aktEnemy->getDeathCooldown() == 0) {
                    objectsToDelete.push_back(aktEnemy);
                } else if (aktEnemy->getFireCooldown() == 0) {
                    Shoot *enemyFire;
                    int direction;
                    /* Bewegungrichtung für den Krug ermitteln
                     * bei bewegendem Gegner in Richtung der Bewegung
                     * bei stillstehenden in Richtung des Spielers
                     */
                    if (aktEnemy->getSpeedX() == 0) {
                        direction = playerObjPointer->getPosX() - aktEnemy->getPosX();
                    } else {
                        direction = playerObjPointer->getSpeedX();
                    }
                    if (direction < 0) {
                        direction = -1;
                    } else {
                        direction = 1;
                    }
                    enemyFire = new Shoot(aktEnemy->getPosX(), aktEnemy->getPosY(), direction, enemy);
                    worldObjects.push_back(enemyFire);
                    scene->addItem(enemyFire);
                    enemyFire = 0;
                }
                aktEnemy = 0;
            }
            speedX = aktMovingObject->getSpeedX();
            speedY = aktMovingObject->getSpeedY();
        }

        aktMovingObject = 0;

        qDebug("%s: x=%4d y=%4d\tvx=%3d vy=%3d",objecttypes[static_cast<int>(aktObject->getType())].c_str(), aktObject->getPosX(),aktObject->getPosY(),speedX,speedY);

    }

    //Grafik - sorgt dafür dass "window" auf den Spieler zentriert bleibt
    window->centerOn(playerObjPointer->getPosX() + 512 - 100 - 0.5*playerObjPointer->getLength(), 384);
}

/**
 * @brief Game::detectCollision
 * Diese Funktion berechnet die Kollisionen, welche zwischen zwei Onjekten, affectedObject und causingObject auftreten. Außerdem wird
 *      die Richtung aus der die Bewegung verursacht wird berechnet
 * Die Kollision wird dabei immer aus Sicht von affectedObject berechnet. So als wäre der Rest des Levels als statisch zu betrachten...
 *
 * @author Simon, johann
 */
void Game::detectCollision(std::list<GameObject*> *objectsToCalculate) {

    int numerator;

    for (std::list<GameObject*>::iterator it=objectsToCalculate->begin(); it != objectsToCalculate->end(); ++it) {

        //aktuelles Gameobjekt herausnehmen
        MovingObject *affectedObject = dynamic_cast<MovingObject*>(*it);
        // Prüfen, ob das aktuelle Objekt überhaupt vom Typ MovingObject ist
        if (affectedObject != 0) {
            // affectedObject ist ein sich bewegendes Objekt

            // Liste möglicher Kollisionen anlegen
            std::list<GameObject*> possibleCollisions;
            /* Möglich Anzahl an Kollisionen WORST CASE:
             *  von links:  4 (bei drei Ebenen) (evtl.5(6) Gegner in mehreren Ebenen 2(3))
             *  von rechts: 5 (bei drei Ebenen) (evtl.6(7) Gegner in mehreren Ebenen 2(3))
             */


//Kollisionen von Rechts
            // vorherige 5 Objekte aus der Liste überprüfen, falls noch so viele in Liste enthalten
            numerator = 0;
            while ((numerator < 5) && (std::prev(it, numerator) != objectsToCalculate->begin())) {
                // fügt den (numerator+1)ten Vorgänger vorne zur Liste der möglichen Kollisionen hinzu
                                                        // dadurch bleibt Reihenfolge erhalten
                possibleCollisions.push_front(*std::prev(it,numerator + 1));
                numerator = numerator + 1;
            }

            /* durchlaufe Liste der möglichen Kollisionen mit posX kleiner/gleich als der des sich bewegenden Objekts
             *      möglichen Kollisinen sind also: vonRechts, vonOben, vonUnten
             */
            while (!(possibleCollisions.empty())) {
                // nehme erstes Objekt aus der Menge (mögliches getroffenes Objekt)
                    // wird als statisches Objekt betrachtet
                GameObject *causingObject = possibleCollisions.front();
                possibleCollisions.pop_front();

                // Kollision feststellen: Dazu ist Überschneidung in X- und Y-Richtung nötig

                // Überschneidung in X-Richtung
                int overlapX = (causingObject->getPosX() + causingObject->getLength()) - affectedObject->getPosX();
                if (overlapX > 0) {
                    /* Objekte überschneiden sich (statisches links von beweglichem)
                     * Lage bezüglich Y-Richtung überprüfen
                     *      3 Möglichkeiten: bewegendes Objekt unter, auf selber Höhe, drüber
                     */
                    if (affectedObject->getPosY() < causingObject->getPosY()) {
                        // bewegendes Objekt unter statischem Objekt    -> vonRechts, vonUnten
                        // overlapY: Überschneidung in Y-Richtung
                        int overlapY = (affectedObject->getPosY() + affectedObject->getHeight()) - causingObject->getPosY();
                        if (overlapY > 0) {
                            // Kollision in Y-Richtung
                        if (overlapX < overlapY) {
                            // Überschneidung in X-Richtung ist größer als in Y-Richtung
                                // Kollision vonUnten
                            collisionStruct collision = {affectedObject, causingObject, fromBelow};
                            collisionsToHandle.push_back(collision);
                        } else if (overlapX == overlapY) {
                            // Überschneidungen gleichgroß
                                // Zwei Möglichkeiten: vonUnten, vonRechts
                            if (!(affectedObject->getSpeedX() < 0)) {
                                // wenn sich bewegendes Objekt nicht nach links bewegt, Kollision vonUnten
                                collisionStruct collision = {affectedObject, causingObject, fromBelow};
                                collisionsToHandle.push_back(collision);
                            } else if ((affectedObject->getSpeedX() < 0) && (affectedObject->getSpeedY() > 0)) {
                                //wenn sich das bewegende Objekt sowohl nach links alsauch nach oben bewegt erzeuge zwei Kollisionen
                                collisionStruct collision = {affectedObject, causingObject, fromBelow};
                                collisionsToHandle.push_back(collision);
                                collision = {affectedObject, causingObject, fromRight};
                                collisionsToHandle.push_back(collision);
                            } else {
                                //wenn sich bewegendes Objekt nicht nach oben bewegt
                                collisionStruct collision = {affectedObject, causingObject, fromRight};
                                collisionsToHandle.push_back(collision);
                            }
                        } else {
                            // Überschneidung in X-Richtung kleiner als in Y-Richtung
                                // Kollision vonRechts
                            collisionStruct collision = {affectedObject, causingObject, fromRight};
                            collisionsToHandle.push_back(collision);
                        }
                        // bewegendes Objekt unter statischem
                        }

                    } else if (affectedObject->getPosY() == causingObject->getPosY()) {
                        // beide Objekte auf selber Höhe                -> vonRechts
                        collisionStruct collision = {affectedObject, causingObject, fromRight};
                        collisionsToHandle.push_back(collision);
                        // Objekte auf selber Höhe

                    } else {
                        // bewegendes Objekt über statischem Objekt     -> vonRechts, vonOben
                        // overlapY: Überschneidung in Y-Richtung
                        int overlapY = (causingObject->getPosY() + causingObject->getHeight()) - affectedObject->getPosY();
                        if (overlapY > 0) {
                            // Kollision in Y-Richtung
                        if (overlapX < overlapY) {
                            // Überschneidung in X-Richtung kleiner als in Y-Richtung
                                // Kollision vonRechts
                            collisionStruct collision = {affectedObject, causingObject, fromRight};
                            collisionsToHandle.push_back(collision);
                            // Überschneidung in X-Richtung ist größer als in Y-Richtung
                                // Kollision vonOben
                        } else {
                            //sonst Kollision vonOben
                                //Ist um eventuelle Fehler beim auftreten des "Dauer-Fallens" zu verhindern
                            collisionStruct collision = {affectedObject, causingObject, fromAbove};
                            collisionsToHandle.push_back(collision);
                        }
                        }
                    }// Lage y-Positionen
                }
            }//while(possibleCollisions)


//Kollisionen von Links
            // nachfolgende 6 Objekte aus der Liste überprüfen, falls noch so viele in Liste enthalten
            numerator = 0;
            while ((numerator < 6) && (std::next(it, numerator) != objectsToCalculate->end())) {
                // fügt den (numerator+1)ten Nachfolger hinten zur Liste der möglichen Kollisionen hinzu
                                                        // dadurch bleibt Reihenfolge erhalten
                possibleCollisions.push_back(*std::next(it, numerator + 1));
                numerator = numerator + 1;
            }

            /* durchlaufe Liste der möglichen Kollisionen mit posX größer/gleich als der des sich bewegenden Objekts
             *      möglichen Kollisinen sind also: vonRechts, vonOben, vonUnten
             */
            while (!(possibleCollisions.empty())) {
                // nehme erstes Objekt aus der Menge (mögliches getroffenes Objekt)
                    // wird als statisches Objekt betrachtet
                GameObject *causingObject = possibleCollisions.front();
                possibleCollisions.pop_front();

                // Kollision feststellen: Dazu ist Überschneidung in X- und Y-Richtung nötig

                // Überschneidung in X-Richtung
                int overlapX = (affectedObject->getPosX() + affectedObject->getLength()) - causingObject->getPosX();
                if (overlapX > 0) {
                    /* Objekte überschneiden sich (statisches rechts von beweglichem)
                     * Lage bezüglich Y-Richtung überprüfen
                     *      3 Möglichkeiten: bewegendes Objekt unter, auf selber Höhe, drüber
                     */
                    if (affectedObject->getPosY() < causingObject->getPosY()) {
                        // bewegendes Objekt unter statischem Objekt    -> vonLinks, vonUnten
                        // overlapY: Überschneidung in Y-Richtung
                        int overlapY = (affectedObject->getPosY() + affectedObject->getHeight()) - causingObject->getPosY();
                        if (overlapY > 0) {
                            // Kollision in Y-Richtung
                        if (overlapX < overlapY) {
                            // Überschneidung in X-Richtung ist größer als in Y-Richtung
                                // Kollision vonUnten
                            collisionStruct collision = {affectedObject, causingObject, fromBelow};
                            collisionsToHandle.push_back(collision);
                        } else if (overlapX == overlapY) {
                            // Überschneidungen gleichgroß
                                // Zwei Möglichkeiten: vonUnten, vonLinks
                            if (!(affectedObject->getSpeedX() > 0)) {
                                // wenn sich bewegendes Objekt nicht nach rechts bewegt, Kollision vonUnten
                                collisionStruct collision = {affectedObject, causingObject, fromBelow};
                                collisionsToHandle.push_back(collision);
                            } else if ((affectedObject->getSpeedX() > 0) && (affectedObject->getSpeedY() > 0)) {
                                //wenn sich das bewegende Objekt sowohl nach rechts alsauch nach oben bewegt, erzeuge zwei Kollisionen
                                collisionStruct collision = {affectedObject, causingObject, fromBelow};
                                collisionsToHandle.push_back(collision);
                                collision = {affectedObject, causingObject, fromLeft};
                                collisionsToHandle.push_back(collision);
                            } else {
                                //wenn sich bewegendes Objekt nicht nach oben bewegt
                                collisionStruct collision = {affectedObject, causingObject, fromLeft};
                                collisionsToHandle.push_back(collision);
                            }
                        } else {
                            // Überschneidung in X-Richtung kleiner als in Y-Richtung
                                // Kollision vonLinks
                            collisionStruct collision = {affectedObject, causingObject, fromLeft};
                            collisionsToHandle.push_back(collision);
                        }
                        // bewegendes Objekt unter statischem
                        }

                    } else if (affectedObject->getPosY() == causingObject->getPosY()) {
                        // beide Objekte auf selber Höhe            -> vonLinks
                        collisionStruct collision = {affectedObject, causingObject, fromLeft};
                        collisionsToHandle.push_back(collision);
                    } else {
                        // bewegendes Objekt über statischem        ->vonOben, vonLinks
                        // overlapY: Überschneidung in Y-Richtung
                        int overlapY = (causingObject->getPosY() + causingObject->getHeight()) - affectedObject->getPosY();
                        if (overlapY > 0) {
                            // Kollision in Y-Richtung
                        if (overlapX < overlapY) {
                            // Überschneidung in X-Richtung kleiner als in Y-Richtung
                                // Kollision vonLinks
                            collisionStruct collision = {affectedObject, causingObject, fromLeft};
                            collisionsToHandle.push_back(collision);
                            // Überschneidung in X-Richtung ist größer als in Y-Richtung
                                // Kollision vonOben
                        } else {
                            //sonst Kollision vonOben
                                //Ist um eventuelle Fehler beim auftreten des "Dauer-Fallens" zu verhindern
                            collisionStruct collision = {affectedObject, causingObject, fromAbove};
                            collisionsToHandle.push_back(collision);
                        }
                        }
                    }// Lage Y-Positionen
                }
            }// while(possibleCollisions)

        } // if (cast)
    } // for (gameObject)
} // function

/**
 * @brief Kollisionen in der Liste collisionsToHandle werden der Reihe nach aus Sicht des affectedObjects bearbeitet.
 * In einer Schleife wird das jeweils erst CollisionEvent bearbeitet. Dabei werden nur an dem Objekt affectedObject Änderungen vorgenommen.
 * Mögliche Objekte: Spieler(player), Gegner(enemy), Bierkrug(shot)
 * mögliche Kollision mit Spieler(player), Hindernis(obstacle), Gegner(enemy), Bierkrug(shot), Power-Up(powerUp)
 *
 * @todo Gamestats sktualisieren/Highscore!!
 * @author Johann (15.6.15)
 */
void Game::handleCollisions() {

    collisionStruct handleEvent;
    int overlap;
    Enemy *handleEnemy;
    Shoot *handleShoot;

    //Liste mit den Events abarbeiten
    while (!collisionsToHandle.empty()) {
        handleEvent = collisionsToHandle.front();
        collisionsToHandle.pop_front();

        switch (handleEvent.affectedObject->getType()) {

        case player: {
            /*Zusammenstöße des Spielers
             *  mit Hindernis, Gegner, Schüssen, PowerUps
             *
             * default: Spieler
             *
             * PowerUps FEHLT!!!!!
             */
            switch (handleEvent.causingObject->getType()) {
            case obstacle: {
                /* Zusammenstoß mit Hindernis
                 * Bewegungsabbruch, Positionskorrektur
                 *      4 Möglichkeiten: von oben, unten, links, rechts
                 */
                switch (handleEvent.direction) {
                case fromLeft: {
                    //Bewegung  in X-Richtungstoppen
                    playerObjPointer->setSpeedX(0);
                    //Überlappung berechnen und Spieler nach links versetzen
                    overlap = (playerObjPointer->getPosX() + playerObjPointer->getLength()) - handleEvent.causingObject->getPosX();
                    playerObjPointer->setPosX(playerObjPointer->getPosX() - overlap);
                    break;
                }
                case fromRight: {
                    //Bewegung in X-Richtung stoppen
                    playerObjPointer->setSpeedX(0);
                    //Überlappung berechnen und Spieler nach rechts versetzen
                    overlap = (handleEvent.causingObject->getPosX() + handleEvent.causingObject->getLength()) - playerObjPointer->getPosX();
                    playerObjPointer->setPosX(handleEvent.causingObject->getPosX() + handleEvent.causingObject->getLength());
                    break;
                }
                case fromAbove: {
                    /* Überlappung berechnen und Spieler nach obern versetzen
                     *      Sprungzustand zurücksetzten
                     */
                    overlap = (handleEvent.causingObject->getPosY() + handleEvent.causingObject->getHeight()) - playerObjPointer->getPosY();
                    playerObjPointer->setPosY(playerObjPointer->getPosY() + overlap);
                    playerObjPointer->resetJumpState();
                    break;
                }
                case fromBelow: {
                    //Wegen Zusammenstoß wird ein Fall initiiert
                    playerObjPointer->abortJump();
                    //Überlappung berechnen und Spieler nach obern versetzen
                    overlap = (playerObjPointer->getPosY() + playerObjPointer->getHeight()) - handleEvent.causingObject->getPosY();
                    playerObjPointer->setPosY(playerObjPointer->getPosY() + overlap);
                    playerObjPointer->resetJumpState();
                    break;
                }
                }

                break;
            }
            case enemy: {
                /* Zusammenstoß mit Gegener
                 *      Spieler läuft in Gegner oder Gegner fällt auf Spieler (sonst siehe affectedObject==enemy)
                 *      Dem Spieler wird Schaden zugefügt und er erhält einen kurzen immunitätsbonus, falls nicht schon vorhanden
                 */

                qDebug("Spieler - Gegner:----wir berühren uns");

                if (!(handleEvent.direction == fromAbove)) {
                    //Überprüfen ob dem Spieler Schaden zugefügt werden kann
                    if (!(playerObjPointer->getImmunityCooldown() > 0)) {
                        handleEnemy = dynamic_cast<Enemy*>(handleEvent.causingObject);
                        //Stirbt der Spieler durch den zugefügten Schaden -> GameOver
                        if (hurtPlayer(handleEnemy->getInflictedDamage())) {
                            gameStats.gameOver = true;
                        } else {
                            //Immunitätsbonus einer haleben Sekunde
                            playerObjPointer->setImmunityCooldown(10);
                        }
                        handleEnemy = 0;
                    }
                }
            }
            case shot: {
                // Spieler kriegt Schaden, Bierkrug zum löschen vormerken, treffen mit eigenem Krug nicht möglich
                handleShoot = dynamic_cast<Shoot*>(handleEvent.causingObject);
                if (hurtPlayer(handleShoot->getInflictedDamage())) {
                    gameStats.gameOver = true;
                }
                objectsToDelete.push_back(handleShoot);
                handleShoot = 0;
                break;
            }
            case powerUp: {
                /* Zusammenstöße mit PowerUps
                 *      Der Spieler erhält zusatzfähigkeiten
                 */
                PowerUp *handlePowerUp = dynamic_cast<PowerUp*> (handleEvent.causingObject);
                playerObjPointer->setHealth(playerObjPointer->getHealth() + handlePowerUp->getHealthBonus());
                playerObjPointer->increaseAmmunation(handlePowerUp->getAmmunationBonus());
                playerObjPointer->setImmunityCooldown(handlePowerUp->getImmunityCooldownBonus());
                playerObjPointer->increaseAlcoholLevel(handlePowerUp->getAlcoholLevelBonus());
                objectsToDelete.push_back(handlePowerUp);
                handlePowerUp = 0;
                break;
            }
            default: {
                /* Zusammenstoß mit Spieler
                 *      nicht möglich
                 */
            }
            }
            break;
        } // end (case player)

        case enemy: {
            /*Zusammenstöße des Gegners
             *  mit Spieler, Hindernis, Schüssen
             *
             * default: Gegner, PowerUps
             *      werden durchlaufen ohne Effekt
             */

            handleEnemy = dynamic_cast<Enemy*>(handleEvent.affectedObject);

            switch (handleEvent.causingObject->getType()) {
            case player: {
                /* Zusammenstoß mit Spieler
                 *      Spieler springt auf Gegner (sonst siehe affectedObject==player)
                 * Der Gegner wird getötet
                 */
                qDebug("Der Spieler tötet mich");
                handleEnemy->setDeath(true);
                break;
            }
            case obstacle: {
                /* Zusammenstoß mit Hindernis
                 *  Bewegungsabbruch, Positionskorrektur, neue Bewegungsrichtung
                 */
                qDebug("I change my direction");
                if (handleEvent.direction == fromAbove) {
                    //Fall wird beendet, X-Bewegung uneingeschränkt
                    handleEnemy->setSpeedY(0);
                    overlap = (handleEvent.causingObject->getPosY() + handleEvent.causingObject->getHeight()) - handleEnemy->getPosY();
                    handleEnemy->setPosY(handleEnemy->getPosY() + overlap);
                } else {
                    // Bewegungsabbruch, neue Bewegungsrichtung
                    handleEnemy->setSpeedX(-handleEnemy->getSpeedX());
                    //PositionsKorrektur
                    if (handleEvent.direction == fromLeft) {
                        //Gegner kommt von links
                        overlap = (handleEnemy->getPosX() + handleEnemy->getLength()) - handleEvent.causingObject->getPosX();
                        handleEnemy->setPosX(handleEnemy->getPosX() - overlap);
                        qDebug("dreh nach rechts");
                    } else {
                        //Gegner kommt von rechts
                        overlap = (handleEvent.causingObject->getPosX() + handleEvent.causingObject->getLength()) - handleEnemy->getPosX();
                        handleEnemy->setPosX(handleEnemy->getPosX() + overlap);
                        qDebug("dreh nach links");
                    }
                }
                break;
            }
            case shot: {
                /* Zusammenstoß mit Bierkrug
                 *  Fügt Schaden zu, falls von Spieler geworfen,
                 *  Bierkrug zum löschen vormerken
                 */
                handleShoot = dynamic_cast<Shoot*>(handleEvent.causingObject);
                if (handleShoot->getOrigin() == player) {
                    //Schaden zufügen
                    handleEnemy->setHealth(handleEnemy->getHealth() - handleShoot->getInflictedDamage());
                    //Bierkrug zum löschen vormerken
                    objectsToDelete.push_back(handleShoot);
                    //Im Falle des Todes
                    if (handleEnemy->getHealth() < 0) {
                        handleEnemy->setDeath(true);
                    }
                }
                handleShoot = 0;
                break;
            }
            default: {
                /*Zusammenstoß mit Gegner, PowerUp
                 *      kein Effekt
                 */
            }
            }
            break;
        }//end (case enemy)

        case shot: {
            /*Zusammenstöße des Bierkrugs
             * mit Hindernis
             *
             * default: Spieler, Gegner, PowerUps
             *      wird jeweils in der Situation Spieler/Gegner bearbeitet, bei PowerUps keinen effekt
             */

            qDebug("It is going to hurt");
            //Bierkrug löschen, bei Kollision mit Hindernis
            if (handleEvent.causingObject->getType() == obstacle) {
                objectsToDelete.push_back(dynamic_cast<Shoot*>(handleEvent.affectedObject));
            }
            break;
        }//end (case shot)
        default: {
            /*Zusammenstöße von Hindernis und PowerUps
             *      NICHT MÖGLICH!!!   da keine MovingObjects
             *
             * default nur um Fehlermeldungen zu vermeiden
             */
        }
        }
    }
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


/**
 * @brief Game::renderGraphics
 * Positionssaktualisierungen der Grafiken aller Beewglichen Objekte
 * @param objectList
 */
void Game::renderGraphics(std::list<GameObject*> *objectList) {
    for (std::list<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        if(dynamic_cast<MovingObject*> (*it) != 0) {
            (*it)->setPos((*it)->getPosX() - 0.5*(*it)->getLength(), yOffset -(*it)->getPosY() - (*it)->getHeight());
        }
    }
}




void Game::colTestLevel() {
    /// Skalierungsfaktor für Objekte im Spiel
    int obs = 10;
/*
    // Erstelle statische Objekte
    GameObject *obstackle1 = new GameObject(40*obs, 0*obs, 6*obs, 12*obs, obstacle);
    GameObject *obstackle2 = new GameObject(60*obs, 0*obs, 6*obs, 12*obs, obstacle);
    GameObject *obstackle3 = new GameObject(90*obs, 0*obs, 6*obs, 12*obs, obstacle);

    // Erstelle PowerUp
    GameObject *powerUp1 = new PowerUp(30*obs, 0*obs, 1,1,1,1);


    // Füge statische Objekte der Liste levelInitial hinzu
    levelInitial.push_back(powerUp1);
    levelInitial.push_back(obstackle1);
    levelInitial.push_back(obstackle2);
    levelInitial.push_back(obstackle3);

    // Erstelle Gegner
    GameObject *enemy1 = new Enemy(46*obs, 1*obs, 1*obs);
    GameObject *enemy2 = new Enemy(70*obs, 0*obs, -1*obs);

    // Füge bewegliche Objekte in zugehörige liste
    levelSpawn.push_back(enemy1);
    levelSpawn.push_back(enemy2);
*/
    // Erstelle das Spieler-Objekt und setze den playerObjPointer
    GameObject *playerObject = new Player(13*obs, 0*obs, 1*obs);

    playerObjPointer = dynamic_cast<Player*>(playerObject);
    playerObjPointer->startJump();
}


/**
 * @brief Game::loadLevelFile
 * @param fileSpecifier
 * Diese Funktion liest Level-Dateien aus und kommt mit wenig Parametern aus.
 * Der Player braucht posX und posY.
 * Enemies brauchen posX, posY und speedX.
 * Obstacles brauchen nur posX, posY ist immer null.
 * Planes (Zwischenebenen) brauchen posX und posY.
 * PowerUps brauchen posX, posY und die jeweiligen Boni.
 * @author Simon
 */
void Game::loadLevelFile(QString fileSpecifier) {
    // Spezifizierte Datei öffnen
    QFile levelFile(fileSpecifier);
    if (!levelFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Datei konnte nicht geöffnet werden!";
    } else {
        // Die Datei wurde erfolgreich geöffnet
        // Die Listen werden geleert
        levelInitial.clear();
        levelSpawn.clear();

        qDebug() << "Lese levelFile mit vorgesetzten Parametern aus:";

        QTextStream fileStream(&levelFile);
        while (!fileStream.atEnd()) {
            QString line = fileStream.readLine();
            //qDebug() << line;
            // Trenne die aktuelle Zeile nach Komma getrennt auf
            QStringList strlist = line.split(",");

            if (strlist.at(0) == "Player") {
                qDebug() << "  Player-Eintrag gefunden.";
                // Erstelle das Spieler-Objekt und setze den playerObjPointer
                GameObject *playerObject = new Player(strlist.at(1).toInt(), strlist.at(2).toInt(), 0);
                playerObjPointer = dynamic_cast<Player*>(playerObject);
            }

            if (strlist.at(0) == "Enemy") {
                qDebug() << "  Enemy-Eintrag gefunden.";
                GameObject *enemyToAppend = new Enemy(strlist.at(1).toInt(), strlist.at(2).toInt(), strlist.at(3).toInt());
                levelSpawn.push_back(enemyToAppend);
            }

            if (strlist.at(0) == "Obstacle") {
                qDebug() << "  Obstacle-Eintrag gefunden.";
                GameObject *obstacleToAppend = new GameObject(strlist.at(1).toInt(), 0, obstacle);
                levelInitial.push_back(obstacleToAppend);
            }

            if (strlist.at(0) == "Plane") {
                qDebug() << "  Eintrag für eine Zwischenebene gefunden.";
                GameObject *planeToAppend = new GameObject(strlist.at(1).toInt(), strlist.at(2).toInt(), 2*playerScale, (playerScale / 3), obstacle);
                levelInitial.push_back(planeToAppend);
            }

            if (strlist.at(0) == "PowerUp") {
                qDebug() << "  PowerUp-Eintrag gefunden.";
                GameObject *powerUpToAppend = new PowerUp(strlist.at(1).toInt(), strlist.at(2).toInt(), strlist.at(3).toInt(), strlist.at(4).toInt(), strlist.at(5).toInt(), strlist.at(6).toInt());
                levelInitial.push_back(powerUpToAppend);
            }

            if (strlist.at(0) == "Boss") {
                qDebug() << "  Boss-Eintrag gefunden.";
            }

        } // end of while

        levelInitial.sort(compareGameObjects());
        levelSpawn.sort(compareGameObjects());

        qDebug() << "Auslesen des levelFile beendet.";
    }
}


int Game::getStepIntervall() {
    return stepIntervall;

}

