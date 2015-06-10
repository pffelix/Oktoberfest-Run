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
    int return_code = game->startGame(); // Spiel starten, in startGame ist der Game-Loop implementiert
    /// @todo startGame() schlechter Name, wenn darin der ganze Loop und damit das ganze Spiel läuft.
    return return_code;                 // Rückgabewert von startGame an Betriebssystem übergeben
}
