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

