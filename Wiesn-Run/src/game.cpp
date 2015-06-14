#include "game.h"
#include <iostream>
#include <unistd.h>

Game::Game() {
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


    // ist das nötig? wird der Konstruktor schon bei der Definition in game.h aufgerufen?
    keyInputs = Input();

    // levelInitial laden
    // worldObjects = levelInitial

    // Player erstellen und in worldObjects einfügen

    // Qt Fenster anzeigen?

    //while(1) {
        //std::cout << ".";
    //}

    sleep(5);
    std::cout << "Game wird beendet\n";
    return 0;
}
