#include "game.h"

#include <QtGui>
#include <QApplication>

#include <iostream>

using namespace std;


/**
 * @brief main
 * main() wird am Anfang aufgerufen. Erstellt eine Instanz von Game und startet dieses.
 * @return 0 bei Erfolg, -1 bei Fehler
 * @author Rupert
 */


int main(int argc, char *argv[]) {
    Game *game = new Game(argc, argv);                  // Spielinstanz erstellen
    //game->run();

    std::cout << "Spiel wird gestartet\n";

    int return_code = game->exec(); // Spiel starten, in exec() ist der Game-Loop implementiert
    return return_code;                 // Rückgabewert von startGame an Betriebssystem übergeben
}
