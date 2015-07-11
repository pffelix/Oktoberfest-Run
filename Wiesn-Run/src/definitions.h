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
#include <chrono>

/**
 * @brief Enumerator für den aktuellen Spielstatus
 * ähnlich zu einer StateMachine
 * wird in step() über switch abgefragt
 * @author Rupert
 */
enum gameState {
    gameIsRunning, gameMenuStart, gameMenuCredits, gameMenuLevel, gameMenuBreak, gameMenuStatisitcs, gameMenuName, gameMenuHighscore, gameMenuHelp
};

/**
 * @brief Anzahl gameloop-Durchläufe pro Sekunde
 * wird in allen Klassen für die CooldownParameter benutzt
 */
const int frameRate = 30;

/**
 * @brief Alkohol, der pro Sekunde abgebaut wird
 */
const int minusAlcoholPerSecond = 30;

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
const int maxSpeed = 3 * (playerScale / frameRate) ;

/// normale Player-Speed
const int playerSpeed = maxSpeed + 1;

/**
 * @brief Fall- / Sprunggeschwindigkeit
 */
const int maxSpeedY = 3 * maxSpeed / 2;

/**
 * @brief maximales Leben
 */
const int maxHealth = 5;
const int maxAlcohol = 1000;

/**
 * @brief PowerUp-Konstanten
 * Hier werden die Konstanten gesetzt, die beim Einsammeln eines PowerUps hinzugefügt werden
 */
const int beerAlcohol = 400;
const int beerHealth = 1;
const int beerAmmo = 1;
const int hendlHealth = 1;
const int hendlAlcoholMalus = -500;

/**
 * @brief Distanzen
 * spawnDistance ist die Distanz vom Spieler zum Objekt, ab der Objekte von levelSpawn nach worldObjects verlegt werden.
 * deleteDistance ist die Distanz von einem Objekt zum Spieler, ab welcher das Objekt gelöscht wird.
 */
const int spawnDistance = 1024;
const int deleteDistance = 200;

/**
 * @brief Enumerator für den Objekt-Typ
 * um welche Art von Objekt handelt es sich
 * @author Johann
 */
enum objectType {
    player, enemy_tourist, enemy_security, obstacle, plane, shot, powerUp, BOSS,
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
    int totalPoints;
    int distanceCovered;
    int alcoholPoints;
    int enemiesKilled;
};



/**
 * @brief Enum für den Audiotype
 *        In diesen Enum wird der Audiotype in einen Integer gewandelt.
 *        Jede ID wird dabei einem Audiotype zugeordnet welcher angibt welches Audiofile zur ID abgespielt werden soll.
 * @author Felix Pfreundtner
 */

enum audioType {
    /// fliegendes Bier: wird solange gesendet wie Bier in der Luft fliegt
    scene_flyingbeer,
    /// auftretender Tourist Gegner: wird gesendet solange Gegner lebt
    scene_enemy_tourist,
    /// auftretender Security Gegner: wird gesendet solange Gegner lebt
    scene_enemy_security,
    /// lebender Boss Gegner: wird gesendet solange Bossgegner lebt
    scene_enemy_boss,
    /// Kollision mit Hinderniss aufgetreten: wird einmal gesendet wenn eine Kollision mit einem Hindernis auftritt (cooldown)
    scene_collision_obstacle,
    /// Spieler hat Schaden am Gegner bezweckt: wird einmal gesendet wenn Schaden auftritt (cooldown)
    scene_collision_enemy,
    /// Spieler hat Schaden genommen: wird einmal gesendet wenn Schaden auftritt (cooldown)
    scene_collision_player,
    /// Kollision mit geworfenen Bier aufgetreten: wird einmal gesendet wenn eine Kollision mit einem geworfenen Bier auftritt (cooldown)
    scene_collision_flyingbeer,
    /// Bier Powerup aufgenommen: wird einmal gesendet wenn Powerup aufgenommen wird (cooldown)
    powerup_beer,
    /// Essens Powerup aufgenommen: wird einmal gesendet wenn Powerup aufgenommen wird (cooldown)
    powerup_food,
    /// Alkohol Status höher als 60%: wird solange gesendet wie Alkoholstatus höher als 60% ist
    status_alcohol,
    /// Leben Status 2 Lebenspunkt3: wird solange gesendet wie Spieler 2 Lebenspunkt3 hat 40% ist
    status_life,
    /// Leben Status 1 Lebenspunkt: wird solange gesendet wie Spieler 1 Lebenspunkt hat
    status_lifecritical,
    /// Gameover des Spielers: wird gesendet wenn der Spieler 0% Lebenstatus hat (cooldown)
    status_dead,
    /// Laufbewegung des Spielers: wird solange gesendet wie Spieler sich bewegt
    player_walk,
    /// Springbewegung des Spielers: wird einmal gesendet wenn der Spiel losspringt (cooldown)
    player_jump,
    /// Hintergrund Musik des Hauptmenüs: wird solange gesendet wie Hauptmenü aktiv ist
    background_menu,
    /// Hintergrund Musik des Highscoremenüs: wird solange gesendet wie Highscoremenü aktiv ist
    background_highscore,
    /// Hintergrund Musik des Levels 1: wird solange gesendet wie Level 1 aktiv ist
    background_level1,
    /// Hintergrund Musik des Levels 2: wird solange gesendet wie Level 2 aktiv ist
    background_level2,
    /// Hintergrund Musik des Levels 3: wird solange gesendet wie Level 3 aktiv ist
    background_level3,
    /// Startton wenn Spiel begonnen wird: wird einmal zu Beginn des Level 1 gesendet (cooldown)
    background_startgame,
    /// Gewinnton wenn Level erfolgreich beendet wurde: wird einmal an jedem Levelende gesendet (cooldown)
    background_levelfinished


};

/**
 * @brief Typdef Struct mit Konstanten für den Audiocooldown jedes Audiotypes
 *        In diesen Konstanten wird festgelegt wie viele millisekunden für ein Event (mit "id=...") eines audioTypes trotz verschwinden in der Grafik nachwievor audioStructs gesendet werden.
 *        Ein 0 bedeteutet, dass kein Cooldown erfolgt, die Audiostructs werden hier solange gesendet wie das Event sichtbar ist.
 * @author Felix
 */
typedef struct {
    std::chrono::duration<int, std::milli> scene_flyingbeer = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> scene_enemy_security = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> scene_enemy_tourist = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> scene_enemy_boss = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> scene_collision_obstacle = std::chrono::milliseconds(500);
    std::chrono::duration<int, std::milli> scene_collision_enemy = std::chrono::milliseconds(1639);
    std::chrono::duration<int, std::milli> scene_collision_player = std::chrono::milliseconds(899);
    std::chrono::duration<int, std::milli> scene_collision_flyingbeer = std::chrono::milliseconds(1211);
    std::chrono::duration<int, std::milli> powerup_beer = std::chrono::milliseconds(2989);
    std::chrono::duration<int, std::milli> powerup_food = std::chrono::milliseconds(3989);
    std::chrono::duration<int, std::milli> status_alcohol = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> status_life = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> status_lifecritical = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> status_dead = std::chrono::milliseconds(4989);
    std::chrono::duration<int, std::milli> player_walk = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> player_jump = std::chrono::milliseconds(700);
    std::chrono::duration<int, std::milli> background_menu = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> background_highscore = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> background_level1 = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> background_level2 = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> background_level3 = std::chrono::milliseconds(0);
    std::chrono::duration<int, std::milli> background_startgame = std::chrono::milliseconds(3000);
    std::chrono::duration<int, std::milli> background_levelfinished = std::chrono::milliseconds(5365);
} audioCooldownStruct;

/**
 * @brief Typdef Struct mit Konstanten für die Distance jedes Audiotypes
 *        In diesen Konstanten wird festgelegt wie weit entfernt ein Event (mit "id=...) eines audioTypes vom Spieler standardmäßig auftritt [Werbereicht 0 (beim spieler) bis 1(maximale Distanz des Fensters).
 *        Ist die Konstante -1 ist die Distance eines Events vom Typ audioType variabel und muss von der Gamelogik bestimmt werden.
 * @author Felix
 */
typedef struct {
    float scene_flyingbeer = -1;
    float scene_enemy_tourist = -1;
    float scene_enemy_security = -1;
    float scene_enemy_boss = -1;
    float scene_collision_obstacle = 0;
    float scene_collision_enemy = 0;
    float scene_collision_player = 0;
    float scene_collision_flyingbeer = 0;
    float powerup_beer = 0;
    float powerup_food = 0;
    float status_alcohol = 0;
    float status_life = 0;
    float status_lifecritical = 0;
    float status_dead = 0;
    float player_walk = 0;
    float player_jump = 0;
    float background_menu = 0.0;
    float background_highscore = 0.1;
    float background_level1 = 0.3;
    float background_level2 = 0.3;
    float background_level3 = 0.3;
    float background_startgame = 0.0;
    float background_levelfinished = 0.0;

} audioDistanceStruct;


/**
 * @brief Struktur für einzelne Audio Events
 * AudioControl arbeitet Events von dieser Struktur ab.
 * Jedes Audioevent hat eine eindeutige int "id", einen enum->integer Gruppen "type" und eine float "distance"
 * und ordnet somit jedem Objekt einen Sound zu, wobei sich die Distanzinformation des Sounds ändern kann.
 * Ein Distanzwert beträgt dabei minimal 0 und maximal 1 (größte Entfernung im Gamefenster).
 * Die Standarddistanzwerte sind in "typedef struct audioDistance" für jeden AudioStruct "type" definiert.
 *
 * Alle in einem Step auftretetenden audioStruct's werden in einer std::list audioevents
 * gesammelt (game.h) und über die Methode update() in jedem Step der Klasse Audiocontrol übergeben.
 * Audiocontrol steuert den richtigen Abspieltyp jedes audioStruct.
 * Nach jedem Step wird die Liste gelöscht und wieder neu mit audioStructs gefüllt.
 * Audio Events welche in der GameLogik nur einmal auftreten, wie ein Powerup aufnehmen, werden mit einem Cooldown Timer
 * zusätzlich länger  an die Liste audioevents angehängt um ein weiteres Abspielen zu garantieren.
 * Die Dauer des Cooldown Timers ist in "typedef struct audioCooldown" für jeden AudioStruct "type" definiert.
 *
 * Ist ein Event mit zu erfolgender Audioausgabe vorhanden wird
 * ein audioStruct mit Eventname und aktueller Distanz des Audio-Events vom
 * Spieler zum Event erstellt.
 * Dieses Audiostruct wird an die Liste audioevents mit allen im Step
 * stattfinden audioStructs angehängt.
 * Ist ein Objekt / Event nachwievor aktiv in der Szene wird das
 * Struct im nächsten Step wieder an die Liste audioevents angehängt und die audioStruct "id" konstant gehalten.
 * Ist ein Objekt nicht mehr in der Szene zu sehen, so muss kein audioStruct übergeben werden.
 * Die audioStruct "id" diese Objekts wird im weiteren Spielverlauf nicht mehr verwendet.
 *
 * Befindet sich z.B. ein Bier mit "id = ..." in der Szene, so ist der "type = scene_beer".
 * In jedem Step muss in der Audio-Struktur die "distance" des Biers zum Spieler
 * aktualisiert werden und an die Liste audioevents angehängt werden.
 * Verschwindet des Bierobjekt so wird das audioStruct nicht mehr übergeben und die "id" nicht mehr verwendet.
 * Gibt es mehrere Bierobjekte so wird das Struct mit Gruppen "type=scene_beer" mit verschiednen "id"'s an die Liste angehängt.
 *
 * Läuft der Spieler im aktuellen Step so wird das audioStruct "player_walk" erstellt("distance" stets 0).
 * Läuft er im nächsten Step nachwievor (hat also seine Position geändert) wird das Audiostruct wieder an die audioevents Liste angehängt.
 * Läuft er nicht mehr wird es nicht mehr an die audioevents liste angehängt.
 *
 * Ist gerade das Level 1 aktiv so wird in jedem Step ein audioStruct mit "ID=..." und "type=background_level1" an die Liste angehängt.
 * Bei Background Musik ist "distance=0.5". Dies bewirkt dass sie leiser als Playersounds (distance = 0) abgespielt wird.
 * @author Felix Pfreundtner
 */
struct audioStruct {
    int id;
    audioType type;
    float distance;
};


/**
 * @brief Struktur für audioevents mit ihrer abspielzeit als Cooldown
 */
struct audioCooldownstruct {
    struct audioStruct audioEvent;
    std::chrono::duration<int, std::milli> cooldown;
};

enum powerUpType {
    beer, food
};

/**
 * @brief Struktur für die States des Spiels
 * Sowohl Sound- als auch Grafik-Ausgabe erhalten aus den States Informationen darüber, was gerade im Spiel passiert,
 * z.B. dass gerade der Spieler angreift, ein Gegner stribt etc.
 * @todo Diese Struktur ist vermutlich überflüssig.
 * @author Simon
 */
struct stateStruct {
    bool gameOver = false;
    int actLevel = 0;
    int audioID_Background = 0;

    bool beerCollected = 0;
    bool chickenCollected = 0;

};


#endif // DEFINITIONS_H
