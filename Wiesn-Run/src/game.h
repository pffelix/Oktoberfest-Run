#ifndef GAME_H
#define GAME_H


#include <list>

#include "definitions.h"
#include "gameobject.h"
#include "player.h"
#include "enemy.h"
#include "shoot.h"
#include "input.h"
#include "audiocontrol.h"
#include "powerup.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <chrono>
#include <QMainWindow>
#include "menu.h"
#include "portaudio.h"
#include "renderGUI.h"
#include "renderbackground.h"
#include <QEvent>
#include <QCloseEvent>
#include <thread>
using namespace std;


/**
 * @brief Struktur für die Events.
 * Enthält affectedObject als Objekt, aus dessen Sicht die Kollision berechnet wurde. affectedObject ist immer ein MovingObject,
 * causingObject kann beides sein.
 * Die Art und Richtung der Kollision werden mit gespeichert.
 *
 * @author Simon, Johann
 */
struct collisionStruct {
    GameObject *affectedObject;
    GameObject *causingObject;
    enum collisionDirection direction;
};

/**
 * @brief Kern-Funktionalität des Spiels
 *
 * Innerhalb der main.cpp wird eine Instanz dieser Klasse angelegt,
 * aus der heraus das gesamte Spiel läuft.
 * Die einzelnen Methoden werden in der game.cpp jeweils erklärt.
 *
 * @author Simon, Johann, Felix, Rupert, Florian
 */
class Game : QObject {
    //Q_OBJECT
public:
    // Konstruktor und Destruktor
    Game(int argc, char *argv[]);
    ~Game();

    // Startet das die Game-Loop, wird einmalig von main() aufgerufen
    int step();

    /// States des Spiels
    struct stateStruct gameStats;
    /// Liste von Kollisionen
    std::list<struct collisionStruct> collisionsToHandle;

    // Starten der Applikation
    int start();

    // Hilfsfunktion
    void setState(enum gameState newState);

protected:
    void timerEvent(QTimerEvent *event);

private:
    // Level starten und beenden
    void startNewGame(QString levelFileName, int levelNum);
    void loadLevelFile(QString fileSpecifier);
    void updateHighScore(std::string mode);
    void displayStatistics();
    void endGame();

    // Funktionen in der Loop
    void appendWorldObjects(Player *playerPointer);
    void reduceWorldObjects(Player *playerPointer);
    void evaluateInput();
    void calculateMovement();
    void detectCollision(std::list<GameObject*> *objectsToCalculate);
    void handleCollisions();
    void updateScore();
    void updateAudioevents();
    void renderGraphics(std::list<GameObject *> *objectList, Player *playerPointer);

    // Funktionen zu Start und Ende der Applikation
    void menuInit();
    void exitGame();
    bool eventFilter(QObject *obj, QEvent *event);

    // Hilfsfunktion
    int getStepIntervall();
    void timeNeeded(string name);


    /// In der Welt befindliche Objekte
    std::list<GameObject*> worldObjects;
    // Statische Objekte, die zu Anfang gespawnt werden
    //std::list<GameObject*> levelInitial;
    /// Objekte die zur Laufzeit dynamisch gespawnt werden
    std::list<GameObject*> levelSpawn;
    /// Zu löschende Schüsse
    std::list<GameObject*> objectsToDelete;
    /// Audiocontrol Objekt, welches aktuelle Audioevents auswertet
    AudioControl *audioOutput;
    /// Audio Wiedergabe Thread, welcher Portaudio Callback Funktion ausführt und Audioevents Blockweise abspielt
    std::thread portaudiothread;
    /// Liste audioevents mit allen im Step aktiven AudioStructs
    std::list<struct audioStruct> audioevents;
    /// Liste mit den Audioevents, die einmal aufgerufen werden, aber eine Längere Spielzeit haben
    std::list<struct audioCooldownstruct> audioStorage;

    /// Breite der Szene
    int sceneWidth;
    /// Länge des Levels
    int levelLength = 0;

    /// Score-Liste
    std::list<struct scoreStruct> scoreList;
    /// Scores
    struct scoreStruct playerScore;

    /// Länge eines Steps
    int stepIntervall;
    /// Spiel Beenden gedrückt
    bool exitGameevent;
    /// Spiel Starten gedrückt
    bool levelStartevent;

    /// Pointer auf Spieler-Objekt
    Player *playerObjPointer;

    /// für das Ausgabefenster QGraphicsView
    QGraphicsView * window;
    /// QGraphicsScene des Levels
    QGraphicsScene * levelScene;

    /// für alle Anzeigen wie Leben,Alkohol,Score,..
    RenderGUI * showGUI;

    /// für die Hintergrundgrafiken
    RenderBackground * showBackground;

    /// Zeiger auf QApplication
    QApplication *appPointer;
    /// für Zeitmessung
    std::chrono::high_resolution_clock::time_point letzterAufruf;
    /// Erstelle Input Objekt zum Aufzeichnen der Keyboard Inputs
    Input *keyInput = new Input();


    // Menüs
    /// aktueller Spielzustand
    enum gameState state = gameMenuStart;
    /// aktuell aktives Menü, null, während das Spiel läuft; wird in setState gesetzt
    Menu *aktMenu = menuStart;

    /// Startmenü
    Menu *menuStart;
    /// Credits-Menü
    Menu *menuCredits;
    /// Levelauswahl-Menü
    Menu *menuLevel;
    /// Pause-Menü
    Menu *menuBreak;
    /// Statistik-Menü
    Menu *menuStatistics;
    /// Namenseingabe-Menü
    Menu *menuName;
    /// Highscore-Menü
    Menu *menuHighscore;
    /// Hilfemenü
    Menu *menuHelp;

    /// zur Unterscheidung und Identifizierung der Menü-Einträge
    enum menuIds {
        menuId_NonClickable,
        menuStartId_NewGame, menuStartId_EndGame, menuStartId_Help, menuStartId_Credits,   // Startmenü
        menuCreditsId_Back, // Credits
        menuLevelId_Back, menuLevelId_Demo, menuLevelId_Level1, menuLevelId_Level2, menuLevelId_Level3, menuLevelId_StartGame,   // Levelauswahl
        menuBreakId_Resume, menuBreakId_EarlyEnd, menuBreakId_EndGame,    // Pause
        menuStatisticsId_Next,  // Statistik
        menuNameId_Next,        // Name eingeben
        menuHighscoreId_Next,   // Highscoretabelle
        menuHelpId_Back         // Hilfemenü
    };

    /// stepCount wird mit jedem Step um ein erhöht
    /// Auslesen der vergangenen Zeit: stepCount * getStepIntervall()
    int stepCount = 0;

    /// audioIDs wird mit jedem AudioEvent erhöht. Jedes AudioEvent erhält eine feste ID
    int audioIDs;
    /// Struktur zur Erstellung von Audio-Cooldown-Events
    audioCooldownStruct audioCooldown;
    /// Struktur zur Erstellung von AudioEvents, gibt die Lautstärke des AudioEvents an
    audioDistanceStruct audioDistance;
    /// Zeitpunkt zur Bestimmung der Dauer eines "Steps". Wird in updateAudioevents benutzt um den Cooldown von Audioevents zu verringern
    chrono::high_resolution_clock::time_point thisStep;
    /// Zeitpunkt zur Bestimmung der Dauer zwischen zwei timeNeeded aufrufen
    chrono::high_resolution_clock::time_point testStep;

};

#endif // GAME_H

