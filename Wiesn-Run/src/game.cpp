#include "game.h"
#include <iostream>
#include <unistd.h>


/**
 * @brief Konstruktor
 * Initialisiert den appPointer
 * @param argc
 * @param argv
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
 */
void Game::timerEvent(QTimerEvent *event)
{
    qDebug("Timer");
    step();
    ///@TODO return von step...
}

/**
 * @brief Erstelle Mockup QApplication app mit Widget inputwindow (Eventfilter installiert) und Zeiger keyInputs auf Input Objekt.
 * Um Funktionen der Tastatur Eingabe entwickeln zu können ist ein Qt Widget Fenster nötig.
 * Auf dem Widget wird ein Eventfilter installiert welcher kontinuierlich Tastureingaben mitloggt.
 * Die Eingaben werden in dem Objekt der Input Klasse gespeichert und können über getKeycomb() abgerufen werden.
 * Das Fenster Mockup kann in einer späteren Code Version ersetzt werden.
 * Der Eventfilter muss dann auf dem neuen Widget Objekt installiert werden.
 *
 * Außerdem wird ein Timer gestartet, der in jedem Intervall timerEvent(...) aufruft, wo dann step() aufgerufen wirt.
 * Das ist dann unsere Game-Loop
 *
 * Hier müssen auch die Sachen rein, die einmahlig beim Starten ausgeführt werden sollen
 * - alles laden, Fenster anzeigen
 * @return Rückgabewert von app.exec()
 * @author Felix Rupert
 */
int Game::start() {
    // levelInitial laden
    // worldObjects = levelInitial

    // Player erstellen und in worldObjects einfügen

    QWidget inputwindow;
    inputwindow.resize(320, 240);
    inputwindow.show();
    inputwindow.setWindowTitle(QApplication::translate("Game Widget", "Game Widget (Input Test)"));
    qDebug("initialize inputwindow");
    Input *keyInputs = new Input();
    inputwindow.installEventFilter(keyInputs);

    Game::startTimer(2000);

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
    return 0;
}
