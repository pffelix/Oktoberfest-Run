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
#include <list>

/**
 * @brief Anzahl gameloop-Durchläufe pro Sekunde
 * wird in allen Klassen für die CooldownParameter benutzt
 */
const int frameRate = 30;

/**
 * @brief Skalierungsfaktor für die Breite des Spielerobjekts bei 1024 Bildschirmbreite:
 *                 Breite:Höhe
 * Spieler, Gegner:     1:2
 * Hindernisse:         (3/2):2     ,     2:(1/3)           dabei ist das erste das Standardhindernis
 * Power-Up:        (2/3):(2/3) ,
 * Krug:            (1/3):(2/3)
 */
const int playerScale = 60;

/**
 * @brief Offsets Spieler <-> linker Fensterrand und Spielebene <-> oberer Fensterrand
 * yOffset: Distanz zwischen obererm Rand (QT Koordinatensystem läuft von oben nach unten) und unterster Spielebene
 *          => Fensterhöhe(768px) - yOffset = 100px
 * playerOffset: Distanz zwischen linkem Rand und Spieler
 */
const int yOffset = 668;
const int playerOffset = 100 + (playerScale/2);

/**
 * @brief Geschwindigkeit mit der sich die beweglichen Objekte durch die Welt bewegen
 */
const int maxSpeed = 2 * playerScale / frameRate;

/// normale Player-Speed
const int playerSpeed = maxSpeed / 2;

/**
 * @brief Fall- / Sprunggeschwindigkeit
 */
const int maxSpeedY = 3 * (playerScale / frameRate);

/**
 * @brief maximales Leben
 */
const int maxHealth = 5;

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
    player, enemy_tourist, enemy_security, obstacle, shot, powerUp, BOSS, plane
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
 * In dieser Struktur werden Name des Spielers, getötete Gegner, zurückgelegte Entfernung und Alkohol-Punkte gespeichert.
 * Alkohol-Punkte erhält der Spieler für einen gewissen Pegel in einem Zeitabschnitt.
 * @todo Das Konzept der Alkohol-Punkte muss noch ausgearbeitet werden.
 * @author Simon
 */
struct scoreStruct {
    std::string name;
    int enemiesKilled;
    int distanceCovered;
    int alcoholPoints;
    int totalPoints;
};

enum audio {
    scene_beer,
    scene_enemy,
    powerup_chicken,
    powerup_beer,
    status_life,
    status_alcohol,
    player_walk,
    player_jump,
    background_menu,
    background_highscore,
    background_level1,
    background_level2,
    background_level3
};


/**
 * @brief Struktur für einzelne Audio Events
 * AudioControl arbeitet Events von dieser Struktur ab.
 * Jedes audioStruct hat eine eindeutige int ID, einen string Gruppen "namen" und eine float Distanzinformation.
 * und ordnet somit jedem Objekt einen Sound zu.
 * Ein Distanzwert beträgt dabei minimal 0 und maximal 1 (größte Entfernung im Gamefenster).
 * Alle in einem Step auftretetenden audioStruct's werden in einer std::list audioevents
 * gesammelt (game.h) und über die Methode update() in jedem Step der Klasse Audiocontrol übergeben.
 * Audiocontrol steuert den richtigen Abspieltyp jedes audioStruct.
 * Nach jedem Step wird die Liste gelöscht und wieder neu mit audioStructs gefüllt.
 * Audio Events welche in der GameLogik nur einmal auftreten wie ein Powerup aufnehmen werden mit einem Cooldown Timer zusätzlich für 1 Sekunde an die Liste audioevents angehängt.
 *
 * Ist ein Event mit zu erfolgender Audioausgabe vorhanden wird
 * ein audioStruct mit Eventname und aktueller Distanz des Audio-Events vom
 * Spieler zum Event erstellt.
 * Dieses Audiostruct wird an die Liste audioevents mit allen im Step
 * stattfinden audioStructs angehängt.
 * Ist ein Objekt / Event nachwievor aktiv in der Szene wird das
 * Struct im nächsten Step wieder an die Liste audioevents angehängt.
 * Ist ein Objekt nicht mehr in der Szene zu sehen, so muss kein audioStruct übergeben werden.
 *
 * Befindet sich z.B. ein Bier in der Szene, so ist der audioStruct "name = scene_beer".
 * In jedem Step muss in der Audio-Struktur die Distanz des Biers zum Spieler
 * aktualisiert werden und an die Liste audioevents angehängt werden.
 * Verschwindet des Bierobjekt so wird das audioStruct nicht mehr übergeben.
 * Gibt es mehrere Bierobjekte so wird das Struct mit Gruppen "name=scene_beer" mit verschiednen Ids und mit anderen Distanzen an die Liste angehängt.
 *
 * Läuft der Spieler im aktuellen Step so wird das audioStruct "player_walk" erstellt("distance" stets 0).
 * Läuft er im nächsten Step nachwievor (hat also seine Position geändert) wird das Audiostruct wieder an die audioevents Liste angehängt.
 * Läuft er nicht mehr wird es nicht mehr an die audioevents liste angehängt.
 *
 * Ist gerade das Level 1 aktiv so wird in jedem Step das audioStruct "background_level1" an die Liste angehängt.
 * Bei Background Musik ist "distance=0.5". Dies bewirkt dass sie leiser als Playersounds (distance = 0) abgespielt wird.
 *
 * Status_ audioStruct's werden in jedem Zeitschritt in dem das Spiel aktiv ist neu an die Liste angehängt.
 * powerup_ audioStruct's werden angehängt wenn gerade das Powerup aufgenommen wird.
 *  Zudem wird über einen Cooldown das objekt nachwievor für etwas länger angehängt (Cooldown Timer = 1 Sekunde).
 *
 * Übersicht über alle audioStruct's:
 * (wird regelmäßig von Felix erweitert, bei Neuigkeiten bitte audioStructs in GameLogik erstellen -> Neuigkeiten sind mit + markiert):
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
    int id;
    audio name;
    float distance;
};

/**
 * @brief Struktur für audioevents mit ihrer abspielzeit als Cooldown
 */
struct audioCooldownstruct {
    struct audioStruct audioEvent;
    int cooldown;
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
