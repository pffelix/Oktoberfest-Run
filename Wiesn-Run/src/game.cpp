#include "game.h"
#include <iostream>
#include <unistd.h>

Game::Game(int argc, char *argv[]) {
    /**
     * @brief Erstelle Mockup QApplication app mit Widget inputwindow (Eventfilter installiert) und Zeiger keyInputs auf Input Objekt.
     * Um Funktionen der Tastatur Eingabe entwickeln zu können ist ein Qt Widget Fenster nötig.
     * Auf dem Widget wird ein Eventfilter installiert welcher kontinuierlich Tastureingaben mitloggt.
     * Die Eingaben werden in dem Objekt der Input Klasse gespeichert und können über getKeycomb() abgerufen werden.
     * Das Fenster Mockup kann in einer späteren Code Version ersetzt werden.
     * Der Eventfilter muss dann auf dem neuen Widget Objekt installiert werden.
     * @author Felix
     */
    QApplication app(argc, argv);
    QWidget inputwindow;
    inputwindow.resize(320, 240);
    inputwindow.show();
    inputwindow.setWindowTitle(QApplication::translate("Game Widget", "Game Widget (Input Test)"));
    qDebug("initialize inputwindow");
    Input *keyInputs = new Input();
    inputwindow.installEventFilter(keyInputs);
    run(app);

}

Game::~Game() {

}

/**
 * @brief Game-Loop
 * Diese Funktion wird von main() aufgerufen und ist für den kompletten Ablauf des Spiels verantwortlich.
 * grober Ablauf:
 * - alles laden, Fenster anzeigen
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
int Game::exec() {
    std::cout << "Game::exec() gestartet\nwarte 5 Sekunden\n";


    // levelInitial laden
    // worldObjects = levelInitial

    // Player erstellen und in worldObjects einfügen

    // Qt Fenster anzeigen?

    //while(1) {
        //std::cout << ".";

        /*
        appendWorldObjects();
        reduceWorldObjects();
        evaluateInput();
        calculateMovement();
        detectCollision();
        correctMovement();
        handleEvents();
        renderGraphics();
        playSound();
        */
    //}

    sleep(5);
    std::cout << "Game wird beendet\n";
    return 0;
}

/**
 * @brief Starte QApplication app
 * @author Felix
 */
int Game::run(QApplication& app) {
    return app.exec();
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
            switch (handleEvent.causingObject->getType()) {
            case obstacle: {
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
