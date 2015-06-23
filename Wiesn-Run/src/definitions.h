/**************************************************************************************************
 * @brief
 * Datei für alle benötigten Datentypen
 *
 * @latestUpdate:
 * include GameObject.h fixed problems
 *
 * @author Johann, Simon
 **************************************************************************************************/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream>


/**
 * @brief wird von der Menu-Klasse zur Auswahl-Änderung benötigt
 * @author Rupert
 */
enum menuSelectionChange {
    up, down, /*enter*/
};

/**
 * @brief Struct zur Beschreibung eines Menü-Eintrags
 * @author Rupert
 */
struct menuEntry {
    std::string name;
    int id;
    int position;
};

/**
 * @brief Enumerator für den aktuellen Spielstatus
 * ähnlich zu einer StateMachine
 * wird in step() über switch abgefragt
 * @author Rupert
 */
enum gameState {
    gameIsRunning, gameMenuStart, gameMenuEnd
};


/**
 * @brief Enumerator für den Objekt-Typ
 * Hier ist der Objekt-Typ gespeichert.
 * @author Johann
 */
enum objectType {
    player, enemy, obstacle, shot, powerUp, BOSS
};

/**
 * @brief Enumerator für die Kollisions-Richtung
 * Zur Bewegungskorrektur muss klar sein, ob der Spieler ein anderes Objekt von der Seite oder von Oben/Unten berührt hat.
 * Da auch aus Gegner-Sicht die Kollision berechnet wird, gibt es auch Kollisionen von rechts.
 * @author Simon
 */
enum collisionDirection {
    fromLeft, fromRight, fromAbove, fromBelow
};

/**
 * @brief Struktur für die Score des Spielers
 * In dieser Struktur werden getötete Gegner, zurückgelegte Entfernung und Alkohol-Punkte gespeichert.
 * Alkohol-Punkte erhält der Spieler für einen gewissen Pegel in einem Zeitabschnitt.
 * @todo Das Konzept der Alkohol-Punkte muss noch ausgearbeitet werden.
 * @author Simon
 */
struct scoreStruct {
    int enemiesKilled;
    int distanceCovered;
    int alcoholPoints;
};

/**
 * @brief Enumerator playTypeEnum
 * Enumerator für die Abspieltypen der Sounds.
 * Wird z.B. ein Bier geworfen, so ist der playType über die gesamte Zeit "continous".
 * Wird das Objekt zerstört, so wird einmal der playType "stop" gesendet.
 * Einmalige Signale werden mit playType "once" gesendet.
 */
enum playTypeEnum {
    continous, stop, once
};

/**
 * @brief Sound-Struktur
 * Der Sound-Engine arbeitet Events von dieser Struktur ab. Jedes Sound-Event hat einen Namen,
 * eine Distanz und einen playType.
 */
struct soundStruct {
    std::string name;
    int distance;
    enum playTypeEnum playType;
};

/**
 * @brief Struktur für die States des Spiels
 * Sowohl Sound- als auch Grafik-Ausgabe erhalten aus den States Informationen darüber, was gerade im Spiel passiert,
 * z.B. dass gerade der Spieler angreift, ein Gegner stribt etc.
 * @todo Diese Struktur ist vermutlich überflüssig.
 * @author Simon
 */
struct stateStruct {
    bool playerJumping;
    bool playerAttacking;
    bool playerRunning;
    bool playerThrowing;
    bool playerHit;
    bool gameOver;

    bool enemyAttacking;
    bool enemyThrowing;
    bool enemyDead;

    bool beerCollected;
    bool chickenCollected;

};


#endif // DEFINITIONS_H
