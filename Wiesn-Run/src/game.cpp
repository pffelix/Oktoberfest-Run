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
    stepSize = 500;

    // Spieler hinzufügen
    worldObjects.push_back(playerObjPointer);
    // Spawn-Distanz setzen
    spawnDistance = 300;
    // Szenen-Breite setzen
    sceneWidth = 300;
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
            calculateMovement();
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
 * @brief Geht die worldObjects durch und aktualisiert bei jedem die Position
 * wird momentan auch über Debug ausgegeben
 * @author Rupert, Johann
 */
void Game::calculateMovement() {
    using namespace std;               // für std::list
    list<GameObject*>::iterator it;     // Iterator erstellen
    /// Schleife startet beim ersten Element und geht bis zum letzen Element durch
    for(it = worldObjects.begin(); it != worldObjects.end(); ++it) {
        GameObject *aktObject = *it;

        string msg = "OBJECT Position: XPos=" + to_string(aktObject->getPosX());
        qDebug("%d Object Position: XPos=%d",aktObject->getType(), aktObject->getPosX());
        qDebug("%d Object Position: YPos=%d",aktObject->getType(), aktObject->getPosY());
        MovingObject *aktMovingObject = dynamic_cast<MovingObject*> (aktObject);    // Versuche GameObject in Moving Object umzuwandeln
        if(aktMovingObject != 0) {
            aktMovingObject->update();          // Wenn der cast klappt, rufe update() auf.
            //falls es sich um einen Gegner handelt feuern
            if (aktMovingObject->getType() == enemy){
                if (dynamic_cast<Enemy*> (aktMovingObject)->getFireCooldown() == 0) {
                    Shoot* enemyFire = new Shoot(aktMovingObject->getPosX(), aktMovingObject->getPosY(), (aktMovingObject->getSpeedX() * 2), enemy);
                    worldObjects.push_back(enemyFire);
                    enemyFire = 0;
                }
            }
            qDebug("Object Speed: XSpeed=%d",aktMovingObject->getSpeedX());
        }

    }
}

/**
 * @brief Game::detectCollision
 * Diese Funktion berechnet die Kollisionen, welche zwischen ObjektA und ObjektB auftreten.
 * Die Kollision wird dabei immer aus Sicht von ObjektA berechnet. D.h. Variablen wie movingRight
 * bedeuten, dass ObjektA sich nach rechts bewegt hat und dabei ObejektB von Links getroffen hat.
 * @todo Objekt-Definitionen mit eventHandling abstimmen, Koordinatendefinition, Overlap-Problem, <= Fälle
 * @author Simon, johann
 */
void Game::detectCollision(std::list<GameObject*> *objectsToCalculate) {

    for (std::list<GameObject*>::iterator it=objectsToCalculate->begin(); it != objectsToCalculate->end(); ++it) {

        //aktuelles Gameobjekt herausnehmen
        MovingObject *handleMovingObject = dynamic_cast<MovingObject*>(*it);
        // Prüfen, ob das aktuelle Objekt überhaupt vom Typ MovingObject ist
        if (handleMovingObject != 0) {

            // Liste möglicher Kollisionen anlegen
            std::list<GameObject*> possibleCollisions;

            // Vorheriges Element hinzufügen, falls currentObject nicht das erste Element ist.
            if (it != objectsToCalculate->begin()) {
                possibleCollisions.push_back(*std::prev(it));
                // Da das vorherige Element erfolgreich hinzugefügt wurde, prüfe, ob noch ein Element hinzugefügt werden kann
                if (std::prev(it) != objectsToCalculate->begin()) {
                    possibleCollision.push_back(*std::prev(it, 2));
                }
            }
            // Nächstes Element hinzufügen, falls currentObject nicht das letze Element ist.
            if (it != objectsToCalculate->end()) {
                possibleCollision.push_back(*std::next(it));
                // Da nächstes Element erfolgreich hinzugefügt wurde, prüfe, ob noch ein Element hinzugefügt werden kann
                if (std::next(it) != objectsToCalculate->end()) {
                    possibleCollision.push_back(*std::next(it, 2));
                }
            }

            // Durchlaufe die Liste der möglichen Kollisionen, bis sie leer ist
            while (!(possibleCollision.empty())) {

                int overlapX;
                int overlapY;

                // Setze das erste Objekt in der Liste als ObjektB (das getroffene Objekt) und lösche es aus der Liste
                GameObject *objB = *possibleCollision.begin();
                possibleCollision.pop_front();

                // Pürfen und Setzen, ob sich A links/rechts bzw. über/unter B befindet
                bool ALeftFromB = objA->getPosX() < objB->getPosX();
                bool AAboveB = (objA->getPosY() + objA->getHeight()) >= (objB->getPosY() + objB->getHeight());

                // Berechne die Überschneidung in X-Richtung abhänging von der relativen Position von A zu B
                if (ALeftFromB) {
                    overlapX = objA->getPosX() + (objA->getLength() / 2) - (objB->getPosX() - (objB->getLength() / 2));
                } else {
                    overlapX = (objB->getPosX() + (objB->getLength() / 2)) - (objA->getPosX() - (objA->getLength() / 2));
                }

                // Berechne die Überschneidung in Y-Richtung abhängig von der relativen Position von A zu B
                if (AAboveB) {
                    overlapY = (objB->getPosY() + (objB->getHeight() / 1)) - (objA->getPosY());
                } else {
                    overlapY = (objA->getPosY() + (objA->getHeight() / 1)) - (objB->getPosY());
                }

                collisionDirection colDir;

                // Prüfe, aus welcher Richtung die Kollision stattgefunden hat.
                // Für eine Kollision muss gelten...
                // ...von Links: (overlapX < overlapY) && (overlapX > 0) && ALeftFromB
                // ...von Rechts: (overlapX < overlapY) && (overlapx > 0) && !ALeftFromB
                //...von Oben: (overlapY < overlapX) && (overlapY > 0) && AAboveB
                //...von Unten: (overlapY < overlapX) && (overlapY > 0) && !AAboveB
                if ((overlapX < overlapY) && (overlapX > 0)) {
                    if (ALeftFromB) {
                        colDir = fromLeft;
                        collisionStruct newCollision = {objA, objB, objA->getCollisionType(), colDir};
                        eventsToHandle.push_back(newCollision);
                        qDebug("->Kollision von Links hat stattgefunden");
                    } else {
                        colDir = fromRight;
                        collisionStruct newCollision = {objA, objB, objA->getCollisionType(), colDir};
                        eventsToHandle.push_back(newCollision);
                        qDebug("->Kollision von Rechts hat stattgefunden");
                    }
                } else {
                    if ((overlapY <= overlapX) && (overlapY > 0)) {
                        if (AAboveB) {
                            colDir = fromAbove;
                            colDir = fromRight;
                            collisionStruct newCollision = {objA, objB, objA->getCollisionType(), colDir};
                            eventsToHandle.push_back(newCollision);
                            qDebug("->Kollision von Oben hat stattgefunden");
                        } else {
                            colDir = fromBelow;
                            colDir = fromRight;
                            collisionStruct newCollision = {objA, objB, objA->getCollisionType(), colDir};
                            eventsToHandle.push_back(newCollision);
                            qDebug("->Kollision von Unten hat stattgefunden");
                        }
                    }
                }

            } // while
        } // if
    } // for
} // function

/**
 * @brief Kollisionen in der Liste eventsToHandle werden der Reihe nach aus Sicht des affectedObjects bearbeitet.
 * In einer Schleife wird das jeweils erst CollisionEvent bearbeitet. Dabei werden nur an dem Objekt affectedObject Änderungen vorgenommen.
 * Mögliche Objekte: Spieler(player), Gegner(enemy), Bierkrug(shot)
 * mögliche Kollision mit Spieler(player), Spielumfeld(obstacle), Gegner(enemy), Bierkrug(shot), Power-Up(powerUp)
 *
 * @author Johann (15.6.15)
 */
void Game::handleCollisions() {

    collisionStruct handleEvent;
    int overlap;
    Enemy *handleEnemy;
    Shoot *handleShoot;

    //Liste mit den Events abarbeiten
    while (!eventsToHandle.empty()) {
        handleEvent = eventsToHandle.front();
        eventsToHandle.pop_front();

        switch (handleEvent.affectedObject->getType()) {

        case player: {
            /*Zusammenstöße des Spielers
             *  mit Umfeld, Gegner, Schüssen, PowerUps
             *
             * default: Spieler
             *
             * PowerUps FEHLT!!!!!
             */
            switch (handleEvent.causingObject->getType()) {
            case obstacle: {
                /* Zusammenstoß mit Umfeld
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
             *  mit Spieler, Umfeld, Schüssen
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
                /* Zusammenstoß mit Umfeld
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
             * mit Umfeld
             *
             * default: Spieler, Gegner, PowerUps
             *      wird jeweils in der Situation Spieler/Gegner bearbeitet, bei PowerUps keinen effekt
             */

            qDebug("It is going to hurt");
            //Bierkrug löschen, bei Kollision mit Spielumfeld
            if (handleEvent.causingObject->getType() == obstacle) {
                objectsToDelete.push_back(dynamic_cast<Shoot*>(handleEvent.affectedObject));
            }
            break;
        }//end (case shot)
        default: {
            /*Zusammenstöße von Umfeld und PowerUps
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
    GameObject *object1 = new GameObject(100,0,60,80,obstacle,stopping);
    GameObject *object2 = new GameObject(180,0,60,80,obstacle,stopping);
    Player *objectPlayer = new Player(20,0,20,60,player,stopping,8);
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
    GameObject *obstackle1 = new GameObject(30*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle2 = new GameObject(40*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle3 = new GameObject(48*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle4 = new GameObject(55*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle5 = new GameObject(76*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle6 = new GameObject(90*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *powerUp1 = new PowerUp(10*obs, 0*obs, 2*obs, 2*obs, 2, -1, 0, 0);
    GameObject *powerUp2 = new PowerUp(20*obs, 0*obs, 2*obs, 2*obs, 0, 2, 1, 0);
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
    GameObject *playerObject = new Player(1*obs, 0*obs, 3*obs, 6*obs, player, stopping, 1*obs);
    playerObjPointer = dynamic_cast<Player*>(playerObject);
}


void Game::loadLevel2() {
    /// Skalierungsfaktor für Objekte im Spiel
    int obs = 10;

    // Erstelle statische Objekte
    GameObject *obstackle1 = new GameObject(40*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle2 = new GameObject(60*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle3 = new GameObject(78*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle4 = new GameObject(95*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle5 = new GameObject(126*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle6 = new GameObject(160*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
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
        powerUps = new PowerUp((2+i)*obs, 0*obs, 2*obs, 2*obs, -1, 2, 1, 0);
        levelInitial.push_back(powerUps);
        powerUps = 0;
    }
    // Sortiere die Liste levelInitial
    levelInitial.sort(compareGameObjects());

    // Erstelle Gegner
    GameObject *enemy1 = new Enemy(50*obs, 0*obs, 2*obs, 6*obs, enemy, contacting, -1*obs);
    GameObject *enemy2 = new Enemy(85*obs, 0*obs, 2*obs, 6*obs, enemy, contacting, -1*obs);
    GameObject *enemy3 = new Enemy(140*obs, 0*obs, 2*obs, 6*obs, enemy, contacting, -1*obs);
    GameObject *speedEnemy1 = new Enemy(135*obs, 0*obs, 2*obs, 8*obs, enemy, contacting, -2*obs);
    levelSpawn.push_back(enemy1);
    levelSpawn.push_back(enemy2);
    levelSpawn.push_back(enemy3);
    levelSpawn.push_back(speedEnemy1);
    // Sortiere die Liste levelSpawn
    levelSpawn.sort(compareGameObjects());

    // Erstelle das Spieler-Objekt und setze den playerObjPointer
    GameObject *playerObject = new Player(2*obs, 2*obs, 2*obs, 6*obs, player, stopping, 1*obs);
    playerObjPointer = dynamic_cast<Player*>(playerObject);
}

void Game::colTestLevel() {
    /// Skalierungsfaktor für Objekte im Spiel
    int obs = 10;

    // Erstelle statische Objekte
    GameObject *obstackle1 = new GameObject(15*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle2 = new GameObject(21*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);
    GameObject *obstackle3 = new GameObject(40*obs, 0*obs, 8*obs, 6*obs, obstacle, stopping);

    // Erstelle PowerUp
    GameObject *powerUp1 = new PowerUp(10*obs, 0*obs, 2*obs, 2*obs, 1,1,1,1);


    // Füge statische Objekte der Liste levelInitial hinzu
    levelInitial.push_back(powerUp1);
    levelInitial.push_back(obstackle1);
    levelInitial.push_back(obstackle2);
    levelInitial.push_back(obstackle3);

    // Erstelle Gegner
    GameObject *enemy1 = new Enemy(30*obs, 0*obs, 2*obs, 6*obs, enemy, contacting, -1*obs);

    // Füge bewegliche Pbjekte in zugehörige liste
    levelSpawn.push_back(enemy1);

    // Erstelle das Spieler-Objekt und setze den playerObjPointer
    GameObject *playerObject = new Player(2*obs, 2*obs, 2*obs, 6*obs, player, stopping, 1*obs);
    playerObjPointer = dynamic_cast<Player*>(playerObject);
}
