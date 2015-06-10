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


/**
 * @brief Enumerator für den Objekt-Typ
 * Hier ist der Objekt-Typ gespeichert.
 * @author Johann
 */
enum objectType {
    player, enemy, obstacle, shot
};

/**
 * @brief Enumerator für den Kollisions-Typ
 * Für die Kollisionsberechnung ist es wichtig, ob eine Kollision das bewegliche Objekt stoppt (stopping),
 * eventuell stoppt (contacting) oder das bewegliche Objekt einfach hindurchgeht (traversing).
 * obstacle: stopping
 * enemy: contacting (das Stoppen hängt davon ab, ob der Player immun ist)
 * beer: traversing
 * @author Johann, Simon
 */
enum collisionType {
    stopping, contacting, travesing
};

/**
 * @brief Enumerator für die Kollisions-Richtung
 * Zur Bewegungskorrektur muss klar sein, ob der Spieler ein anderes Objekt von der Seite oder von Oben/Unten berührt hat.
 * Da auch aus Gegner-Sicht die Kollision berechnet wird, gibt es auch Kollisionen von rechts.
 * @author Simon
 */
enum collisionDirection {
    fromLeft, fromRight, fromAbove, fromBelow
}; // the collisionDirection tells whether an enemy gets killed or whether we end up on top of an object

/**
 * @brief Struktur für die Events
 * Enthält objectA als Objekt, aus dessen Sicht die Kollision berechnet wurde. objectA ist immer ein MovingObject,
 * objectB kann beides sein.
 * Die Art und Richtung der Kollision werden mit gespeichert.
 * @author Simon
 */
struct eventStruct {
    GameObject objectA;
    GameObject objectB;
    enum collisionType collision;
    enum collisionDirection direction;
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
 * @brief Struktur für die States des Spiels
 * Sowohl Sound- als auch Grafik-Ausgabe erhalten aus den States Informationen darüber, was gerade im Spiel passiert,
 * z.B. dass gerade der Spieler angreift, ein Gegner stribt etc.
 * @todo Es fehlen noch die States selbst.
 * @author Simon
 */
struct stateStruct {
    bool playerJumping;
    bool playerAttacking;
    bool playerRunning;
    bool playerThrowing;
    bool playerHit;
    bool gameOver;

    bool enemyHit;
    bool enemyAttacking;
    bool enemyThrowing;
    bool enemyDead;

    bool beerCollected;
    bool chickenCollected;
};


#endif // DEFINITIONS_H
