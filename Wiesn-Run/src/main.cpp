#include "game.h"
#include <QtGui>
#include <QApplication>
#include <QWidget>
using namespace std;

Game game;


/**
 * @brief main
 * main() wird am Anfang aufgerufen. Erstellt eine Instanz von Game und startet dieses.
 * @return 0 bei Erfolg, -1 bei Fehler
 * @author Rupert
 */

int main(int argc, char *argv[]) {

    /**
     * @brief Erstelle ein Widget Mockup inputwindow und einen Zeiger keyInputs auf ein neues Input Objekt.
     * Um Funktionen der Tastatur Eingabe entwickeln zu können ist ein Qt Widget Fenster nötig.
     * Auf dem Widget wird ein Eventfilter installiert welcher kontinuierlich Tastureingaben mitloggt.
     * Die Eingaben werden in dem Objekt der Input Klasse gespeichert und können über getKeycomb() abgerufen werden.
     * Das Widget kann in einer später Version durch ein Widget der Game Klasse ersetzt werden.
     * Der Eventfilter muss dann auf dem neuen Widget Objekt installiert werden.
     * @author Felix
     */
    QApplication app(argc, argv);
    QWidget inputwindow;
    inputwindow.resize(320, 240);
    inputwindow.show();
    inputwindow.setWindowTitle(QApplication::translate("Main Widget", "Main Widget (Input Test)"));
    return app.exec();
    Input *keyInputs = new Input();
    inputwindow.installEventFilter(keyInputs);

    Game *game;
    game = new Game();                  // Spielinstanz erstellen
    int return_code = game->exec(); // Spiel starten, in exec() ist der Game-Loop implementiert
    return return_code;                 // Rückgabewert von startGame an Betriebssystem übergeben
}
