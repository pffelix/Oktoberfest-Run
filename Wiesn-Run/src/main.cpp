#include "game.h"

using namespace std;

Game game;


/**
 * @brief main
 * main() wird am Anfang aufgerufen. Erstellt eine Instanz von Game und startet dieses.
 * @return 0 bei Erfolg, -1 bei Fehler
 * @author Rupert
 */
int main() {
    Game *game;
    game = new Game();                  // Spielinstanz erstellen
    int return_code = game->exec(); // Spiel starten, in exec() ist der Game-Loop implementiert
    return return_code;                 // Rückgabewert von startGame an Betriebssystem übergeben
}
