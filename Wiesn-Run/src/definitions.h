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
 * @brief Anzahl gameloop-Durchläufe pro Sekunde
 * wird in allen Klassen für die CooldownParameter benutzt
 */
const int frameRate = 20;

/**
 * @brief Skalierungsfaktor für die Breite des Spielerobjekts bei 1024 Bildschirmbreite:
 *                 Breite:Höhe
 * Spieler, Gegner:     1:2
 * Hindernisse:         1:2     ,     2:(1/3)           dabei ist das erste das Standardhindernis
 * Power-Up:        (2/3):(2/3) ,
 * Krug:            (1/3):(2/3)
 */
const int playerScale = 60;

/**
 * @brief Geschwindigkeit mit der sich die beweglichen Objekte durch die Welt bewegen
 */
const int maxSpeed = 2 * playerScale / frameRate;

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
 * um welche Art von Objekt handelt es sich
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
 * @brief Audio-Struktur
 * AudioControl arbeitet Events von dieser Struktur ab.
 * Jedes audioStruct hat einen Namen und eine Distanz und ordnet einem Objekt einen Sound zu.
 * Die Distanz beträgt dabei minimal 0 und maximal 1 (größte Entfernung im Gamefenster).
 * Alle in einem Step auftretetenden audioStruct's werden in einer std::list audiostructs
 * gesammelt (game.h) und über die Methode update() in jedem Step der Klasse Audiocontrol übergeben.
 * Audiocontrol steuert den richtigen Abspieltyp jedes audioStruct.
 * Nach jedem Step wir die Liste gelöscht und wieder neu mit audioStructs gefüllt.
 *
 * Ist ein Event mit zu erfolgender Audioausgabe vorhanden wird
 * ein audioStruct mit Eventname und aktueller Distanz des Audio-Events vom
 * Spieler zum Event erstellt.
 * Dieses Audiostruct wird an die Liste audiostructs mit allen im Step
 * stattfinden audiostructs angehängt.
 * Ändern sich hierbei die Positionswerte eines Objektes von einem Step zu
 * einem anderen Step (was bedeteut, dass das Objekt nachwievor aktiv ist) wird das
 * Struct wieder an die Liste audiostructs angehängt
 * Ändern sich die Werte nicht, so muss kein audioStruct übergeben werden.
 *
 * Befindet sich z.B. ein Bier in der Szene, so ist der "name = scene_beer"
 * In jedem Step muss in der Audio-Struktur die Distanz des Biers zum Spieler
 * aktualisiert werden und an die Liste audiostructs angehängt werden.
 * Verschwindet des Bierobjekt so wird das audioStruct nicht mehr übergeben.
 * Gibt es mehrer Bierobjekte so wird das Struct scene_beer mehrmals an die Liste (mit anderer Distanz) angehängt.
 *
 * Läuft der Spieler im aktuellen Step so wird das audioStruct "player_walk" erstellt("distance" stets 0).
 * Läuft er im nächsten Step nachwievor (hat also seine Position geändert) wird das Audiostruct wieder an die Liste angehängt.
 * Läuft er nicht mehr wird es nicht mehr an die audiostructs liste angehängt.
 *
 * Ist gerade das Level 1 aktiv so wird in jedem Step das audioStruct "background_level1" an die Liste angehängt.
 * Bei Background Musik ist "distance=0.5". Dies bewirkt dass sie leiser als Playersounds (distance = 0) abgespielt wird.
 *
 * Status_ audioStruct's werden in jedem Zeitschritt in dem das Spiel aktiv ist neu an die Liste angehängt.
 * powerup_ audioStruct's werden einmal angehängt wenn gerade das Powerup aufgenommen wird.
 *
 * Übersicht über alle audioStruct's (wird regelmäßig von Felix erweitert, bei Neuigkeiten bitte audioStructs in GameLogik erstellen):
 *
 * scene_beer (distance = variabele)
 * scene_enemy (distance = variable)
 *
 * powerup_chicken (distance = 0)
 * powerup_beer (distance = 0)
 *
 * status_life (distance = 0)
 * status_alcohol (distance = 0)
 *
 * player_walk (distance = 0)
 * player_jump (distance = 0)
 *
 * background_menu (distance = 1)
 * background_highscore (distance=1)
 * background_level1 (distance = 0.5)
 * background_level2 (distance = 0.5)
 * background_level3 (distance = 0.5)
 *
 *
 * @author Felix Pfreundtner
 */
struct audioStruct {
    std::string name;
    int distance;
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
