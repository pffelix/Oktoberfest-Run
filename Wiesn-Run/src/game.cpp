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

/**
 * @brief Game::detectCollision
 * Diese Funktion berechnet die Kollisionen, welche zwischen ObjektA und ObjektB auftreten.
 * Die Kollision wird dabei immer aus Sicht von ObjektA berechnet. D.h. Variablen wie movingRight
 * bedeuten, dass ObjektA sich nach rechts bewegt hat und dabei ObejektB von Links getroffen hat.
 * @todo Auslesen und durchgehen der Liste, setzen der Variablen, Erstellen der Kollisionsevents
 * @author Simon
 */
void Game::detectCollision() {

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

    bool horizontalCollision;

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

    }



}
