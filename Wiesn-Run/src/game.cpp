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

    // Level erstellen bedeutet levelInitial und levelSpawn füllen
    //makeTestWorld();
    //loadLevel1();
    //loadLevel2();
    colTestLevel();

    // Fundamentale stepSize setzen
    stepSize = 1000;

    // Spieler hinzufügen
    worldObjects.push_back(playerObjPointer);
    // Spawn-Distanz setzen
    spawnDistance = 1000;
    // Szenen-Breite setzen
    sceneWidth = 1000;
    // Zeiger auf Objekte aus levelInitial in worldObjects verlegen
    while (!(levelInitial.empty())) {
        GameObject *currentObject = *levelInitial.begin();
        worldObjects.push_back(currentObject);
        levelInitial.pop_front();
    }

    // Menüs erstellen
    menuStart = new Menu(new std::string("Wiesn-Run"));
    menuStart->addEntry("Spiel starten",menuId_StartGame);
    menuStart->addEntry("Spiel beenden", menuId_EndGame);

    menuEnd = new Menu(new std::string("Game Over"));
    menuEnd->addEntry("Highscore anzeigen",menuId_Highscore);
    menuEnd->addEntry("Credits anzeigen",menuId_Credits);
    menuEnd->addEntry("zurück zum Anfang",menuId_GotoStartMenu);

    // QGraphicsView Widget (Anzeigefenster) erstellen und einstellen
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1024,768);
    window = new QGraphicsView(scene);
    window->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    window->setFixedSize(1024,768);
    window->setWindowTitle(QApplication::translate("Game Widget", "Game Widget (Input Test)"));
    window->show();
    qDebug("initialize window");

    // Event Filter installieren
    window->installEventFilter(keyInput);

    // Timer installieren
    qDebug("Starte Timer mit 500msec-Intervall");
    Game::startTimer(stepSize);

    return appPointer->exec();
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
                menuEnd->changeSelection(menuSelectionChange::up);
            }
            if(keyInput->getKeyactions().contains(Input::Keyaction::Down)) {
                menuEnd->changeSelection(menuSelectionChange::down);
            }

            break;

        case gameMenuStart:
            menuStart->display();

            // Enter?
            if(keyInput->getKeyactions().contains(Input::Keyaction::Enter)) {
                // Menüpunkt ausgewählt
                switch(menuStart->getSelection()->id) {
                    case menuId_StartGame:
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
                menuStart->changeSelection(menuSelectionChange::up);
            }
            if(keyInput->getKeyactions().contains(Input::Keyaction::Down)) {
                menuStart->changeSelection(menuSelectionChange::down);
            }

            break;
        case gameIsRunning:
            // Menü bei ESC
            if(keyInput->getKeyactions().contains(Input::Keyaction::Exit)) {
                state = gameMenuEnd;
            }

            worldObjects.sort(compareGameObjects());
            qDebug("---Nächster Zeitschritt---");

            appendWorldObjects(playerObjPointer);
            reduceWorldObjects(playerObjPointer);
            //    evaluateInput();
            worldObjects.sort(compareGameObjects());
            calculateMovement();
            worldObjects.sort(compareGameObjects());
            detectCollision(&worldObjects);
            handleCollisions();

            //    correctMovement();
            //    handleEvents();
            renderGraphics(&worldObjects, playerObjPointer);
            //    playSound();
            break;
    }

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
            delete currentObject;
        }
    }
}

void Game::evaluateInput() {

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
    list<GameObject*>::iterator it;     // Iterator erstellen
    /// Schleife startet beim ersten Element und geht bis zum letzen Element durch
    for(it = worldObjects.begin(); it != worldObjects.end(); ++it) {
        GameObject *aktObject = *it;

        qDebug("%d Object Position: XPos=%d",aktObject->getType(), aktObject->getPosX());
        qDebug("%d Object Position: YPos=%d",aktObject->getType(), aktObject->getPosY());
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
                    enemyFire = 0;
                }
                aktEnemy = 0;
            }
            qDebug("Object Speed: XSpeed=%d",aktMovingObject->getSpeedX());
        }
        aktMovingObject = 0;
    }
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
                    //Bewegung in Y-Richtung stoppen, Sprung beenden!!
                    playerObjPointer->setSpeedY(0);
                    playerObjPointer->resetJump();
                    //Überlappung berechnen und Spieler nach obern versetzen
                    overlap = (handleEvent.causingObject->getPosY() + handleEvent.causingObject->getHeight()) - playerObjPointer->getPosY();
                    playerObjPointer->setPosY(playerObjPointer->getPosY() + overlap);
                    break;
                }
                case fromBelow: {
                    //Wegen Zusammenstoß wird ein Fall initiiert
                    playerObjPointer->setFall();
                    //Überlappung berechnen und Spieler nach obern versetzen
                    overlap = (playerObjPointer->getPosY() + playerObjPointer->getHeight()) - handleEvent.causingObject->getPosY();
                    playerObjPointer->setPosY(playerObjPointer->getPosY() + overlap);
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
 * @param objectList
 * @param playerPointer
 */
void Game::renderGraphics(std::list<GameObject*> *objectList, Player *playerPointer) {

    scene->clear();
    window->viewport()->update();

    int obstacleCount=0, enemyCount=0, attackPowerUpCount=0;

    // Lege leere Liste an um Zeiger auf Objekte in der Szene zu speichern.
    std::list<GameObject*> objToDisplay;

    // Durchlaufe die objectList (worldObjects) von Anfang bis Ende. Ist ein Objekt näher als die Szenenbreite
    // am Spieler dran, so könnte es in der Szene sein und wird in die Liste aufgenommen.
    for (std::list<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {

        bool insideSceneRight = ( (*it)->getPosX() - playerPointer->getPosX() - ((*it)->getLength()/2) ) <= sceneWidth;
        bool insideSceneLeft = ( (*it)->getPosX() - playerPointer->getPosX() + ((*it)->getLength()/2) ) >= 0;

        if ( insideSceneLeft && insideSceneRight && ( (*it) != playerPointer) ) {
            objToDisplay.push_back(*it);
            if((*it)->getType() == obstacle) {
                obstacleCount ++;
            }
            else if ((*it)->getType() == enemy) {
                enemyCount ++;
            }
            else if (( (*it)->getType() == shot) || ( (*it)->getType() == powerUp) ) {
                attackPowerUpCount ++;
            }
        }
    }

    RenderObstacle *renderobstacles = new RenderObstacle[obstacleCount];
    RenderEnemy *renderenemys = new RenderEnemy[enemyCount];
    //RenderAttack *renderattacks = new RenderAttack[attackPowerUpCount];

    // Durchlaufe objToDisplay, bis die Liste leer ist.
    while (!(objToDisplay.empty())) {
        // Setze Zeiger currentObj auf das erste Objekt in der Liste.
        GameObject *currentObj = *objToDisplay.begin();
        // Lösche den Zeiger auf das erste Objekt aus der Liste.
        objToDisplay.pop_front();

        int PosX = currentObj->getPosX() - playerPointer->getPosX() - (currentObj->getLength()/2);

        if( currentObj->getType() == obstacle) {
            obstacleCount --;
            renderobstacles[obstacleCount].render(PosX);
            scene->addItem(renderobstacles+obstacleCount);
        }
        else if( currentObj->getType() == enemy) {
            enemyCount --;
            renderenemys[enemyCount].render(PosX);
            scene->addItem(renderenemys+enemyCount);
        }
        else if( currentObj->getType() == shot) {

        }
        else if( currentObj->getType() == powerUp) {

        }
    } // Ende der while-Schleife

    RenderPlayer * renderPlayer = new RenderPlayer;
    scene->addItem(renderPlayer);

    QImage * img = new QImage(1024,768,QImage::Format_ARGB32_Premultiplied);
    QPainter * painter = new QPainter(img);
    scene->render(painter);

    QGraphicsPixmapItem * item;
    item = new QGraphicsPixmapItem;
    item->setPixmap(QPixmap::fromImage(*img));
    scene->addItem(item);

    delete [] renderobstacles;
    delete renderPlayer;
}

/**
 * @brief Game::playSound
 * @param soundEvents
 */
void Game::playSound(std::list<struct soundStruct> *soundEvents) {

    /// @todo Sound-Overhead hierher

    while (!(soundEvents->empty())) {
        // Kopiere erstes Objekt in der Liste nach currentSound
        soundStruct currentSound = *soundEvents->begin();
        // Entferne Element aus Liste.
        soundEvents->pop_front();

        /// @todo Verarbeite Sound.
    }

    /// @todo Sound-Aufräumarbeiten

}

/**
 * @brief Erstellt ein paar Test-Objekte in worldObjects
 * Was wird erstellt:
 * - Objekt1 mit v=0 an x=100,y=0
 * - Objekt2 mit v=0 an x=180,y=0
 * - ObjektPlayer mit v=8 an x=20,y=0
 * Die Objekte sind 60 breit und 80 hoch. Dimensionen müssen immer durch zwei teilbar sein.
 * @author Rupert, Simon
 */
void Game::makeTestWorld() {
    GameObject *object1 = new GameObject(100,0,60,80,obstacle);
    GameObject *object2 = new GameObject(180,0,60,80,obstacle);
    Player *objectPlayer = new Player(20,0,8);
    worldObjects.push_back(object1);
    worldObjects.push_back(object2);
    worldObjects.push_back(objectPlayer);

}


/**
 * @brief Game::makeLevel1
 * Erstellt die Listen levelInitial und levelSpawn für den ersten Level. Diese müssen dann ausgelesen werden.
 * Der Spieler wird auch als GameObject erstellt. Um den Zeiger auf das Spielerobjekt playerObjPointer setzen
 * zu können, wird ein dynamic_cast auf das Spieler-Objekt ausgeführt.
 * @author Simon
 */
void Game::loadLevel1() {
    /// Skalierungsfaktor für Objekte im Spiel
    int obs = 10;

    // Erstelle statische Objekte
    GameObject *obstackle1 = new GameObject(30*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle2 = new GameObject(40*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle3 = new GameObject(48*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle4 = new GameObject(55*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle5 = new GameObject(76*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle6 = new GameObject(90*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *powerUp1 = new PowerUp(10*obs, 0*obs, 1,1,1,1);
    GameObject *powerUp2 = new PowerUp(20*obs, 0*obs, 1,1,1,1);
    // Füge statische Objekte der Liste levelInitial hinzu
    levelInitial.push_back(obstackle1);
    levelInitial.push_back(obstackle2);
    levelInitial.push_back(obstackle3);
    levelInitial.push_back(obstackle4);
    levelInitial.push_back(obstackle5);
    levelInitial.push_back(obstackle6);
    levelInitial.push_back(powerUp1);
    levelInitial.push_back(powerUp2);
    // Sortiere die Liste levelInitial
    levelInitial.sort(compareGameObjects());

    // Erstelle das Spieler-Objekt und setze den playerObjPointer
    GameObject *playerObject = new Player(1*obs, 0*obs, 1*obs);
    playerObjPointer = dynamic_cast<Player*>(playerObject);
}


void Game::loadLevel2() {
    /// Skalierungsfaktor für Objekte im Spiel
    int obs = 10;

    // Erstelle statische Objekte
    GameObject *obstackle1 = new GameObject(40*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle2 = new GameObject(60*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle3 = new GameObject(78*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle4 = new GameObject(95*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle5 = new GameObject(126*obs, 0*obs, 8*obs, 6*obs, obstacle);
    GameObject *obstackle6 = new GameObject(160*obs, 0*obs, 8*obs, 6*obs, obstacle);
    // Füge statische Objekte der Liste levelInitial hinzu
    levelInitial.push_back(obstackle1);
    levelInitial.push_back(obstackle2);
    levelInitial.push_back(obstackle3);
    levelInitial.push_back(obstackle4);
    levelInitial.push_back(obstackle5);
    levelInitial.push_back(obstackle6);
    // Erstelle und Füge PowerUps hinzu
    GameObject *powerUps;
    for (int i = 0; i < 3; i++) {
        powerUps = new PowerUp((2+i)*obs, 0*obs, -1, 2, 1, 0);
        levelInitial.push_back(powerUps);
        powerUps = 0;
    }
    // Sortiere die Liste levelInitial
    levelInitial.sort(compareGameObjects());

    // Erstelle Gegner
    GameObject *enemy1 = new Enemy(50*obs, 0*obs, -1*obs);
    GameObject *enemy2 = new Enemy(85*obs, 0*obs, -1*obs);
    GameObject *enemy3 = new Enemy(140*obs, 0*obs, -1*obs);
    GameObject *speedEnemy1 = new Enemy(135*obs, 0*obs, -2*obs);
    levelSpawn.push_back(enemy1);
    levelSpawn.push_back(enemy2);
    levelSpawn.push_back(enemy3);
    levelSpawn.push_back(speedEnemy1);
    // Sortiere die Liste levelSpawn
    levelSpawn.sort(compareGameObjects());

    // Erstelle das Spieler-Objekt und setze den playerObjPointer
    GameObject *playerObject = new Player(2*obs, 2*obs, 1*obs);
    playerObjPointer = dynamic_cast<Player*>(playerObject);
}

void Game::colTestLevel() {
    /// Skalierungsfaktor für Objekte im Spiel
    int obs = 10;

    // Erstelle statische Objekte
    GameObject *obstackle1 = new GameObject(0*obs, 0*obs, 6*obs, 6*obs, obstacle);
    GameObject *obstackle2 = new GameObject(50*obs, 0*obs, 6*obs, 6*obs, obstacle);
    GameObject *obstackle3 = new GameObject(63*obs, 0*obs, 8*obs, 6*obs, obstacle);

    // Erstelle PowerUp
    GameObject *powerUp1 = new PowerUp(30*obs, 0*obs, 1,1,1,1);


    // Füge statische Objekte der Liste levelInitial hinzu
    levelInitial.push_back(powerUp1);
    levelInitial.push_back(obstackle1);
    levelInitial.push_back(obstackle2);
    levelInitial.push_back(obstackle3);

    // Erstelle Gegner
    GameObject *enemy1 = new Enemy(20*obs, 1*obs, 1*obs);
    GameObject *enemy2 = new Enemy(44*obs, 0*obs, -1*obs);

    // Füge bewegliche Pbjekte in zugehörige liste
    levelSpawn.push_back(enemy1);
    levelSpawn.push_back(enemy2);

    // Erstelle das Spieler-Objekt und setze den playerObjPointer
    GameObject *playerObject = new Player(57*obs, 2*obs, 0*obs);
    playerObjPointer = dynamic_cast<Player*>(playerObject);
}
