#ifndef GAME_H
#define GAME_H


#include <list>
#include <vector>

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
#include "menu.h"
#include "portaudio.h"
using namespace std;

/**
 * @brief Struktur für die Events
 * Enthält affectedObject als Objekt, aus dessen Sicht die Kollision berechnet wurde. affectedObject ist immer ein MovingObject,
 * causingObject kann beides sein.
 * Die Art und Richtung der Kollision werden mit gespeichert.
 * @author Simon, Johann(15.6)
 */
struct collisionStruct {
    GameObject *affectedObject;
    GameObject *causingObject;
    enum collisionDirection direction;
};

/**
 * @brief Game-Klasse
 * Die Game-Klasse bündelt alle Kern-Funktionalitäten des Spiels.
 * Innerhalb der main.cpp wird eine Instanz dieser Klasse angelegt,
 * aus der heraus das gesamte Spiel läuft.
 * Die einzelnen Methoden werden in der game.cpp jeweils erklärt.
 *
 * @lastChanges funtion handleCollisions hinzugefügt
 *
 * @author Simon, Johann, Felix
 */
class Game : QObject {
    //Q_OBJECT
public:
    /// Konstruktor und Destruktor
    Game(int argc, char *argv[]);
    ~Game();

    // Startet das die Game-Loop, wird einmalig von main() aufgerufen
    int step();
    // Startet die Mockup QApplication app
    int run(QApplication& app);

    struct stateStruct gameStats;
    // Liste von Kollisionen
    std::list<struct collisionStruct> collisionsToHandle;

    /// Starten der Applikation
    int start();

    /// Hilfsfunktion
    void setState(enum gameState newState);

protected:
    void timerEvent(QTimerEvent *event);

private:
    /// Level starten und beenden
    void startNewGame(QString levelFileName, int levelNum);
    void loadLevelFile(QString fileSpecifier);
    void updateHighScore(std::string mode);
    void displayStatistics();
    void endGame();

    /// Funktionen in der Loop
    void appendWorldObjects(Player *playerPointer);
    void reduceWorldObjects(Player *playerPointer);
    void evaluateInput();
    void calculateMovement();
    void detectCollision(std::list<GameObject*> *objectsToCalculate);
    void handleCollisions();
    void updateScore();
    void updateAudio();
    void renderGraphics(std::list<GameObject *> *objectList, Player *playerPointer);

    /// Funktionen zu Start und Ende der Applikation
    void menuInit();
    void exitGame();

    /// Hilfsfunktion
    int getStepIntervall();
    void timeNeeded(string name);


    /// In der Welt befindliche Objekte
    std::list<GameObject*> worldObjects;
    /// Statische Objekte, die zu Anfang gespawnt werden
    //std::list<GameObject*> levelInitial;
    /// Objekte die zur Laufzeit dynamisch gespawnt werden
    std::list<GameObject*> levelSpawn;
    /// Zu löschende Schüsse
    std::list<GameObject*> objectsToDelete;
    /// Audiocontrol Objekt zum Erzeugen der Soundausgabe
    AudioControl *audioOutput;
    /// Error Variable von PortAudio
    PaError paerror;
    /// Liste audioevents mit allen im Step stattfindenden AudioStructs
    std::list<struct audioStruct> audioevents;
    /// Liste mit den Audioevents die einmal aufgerufen werden aber eine Längere Spielzeit haben
    std::list<struct audioCooldownstruct> audioStorage;

    /// Breite der Szene
    int sceneWidth;
    /// Länge des Levels
    int levelLength = 0;
    std::list<struct scoreStruct> scoreList;
    struct scoreStruct playerScore;


    int stepIntervall;
    Player *playerObjPointer;

    /// für das Ausgabefenster QGraphicsView
    QGraphicsScene * levelScene;
    QGraphicsView * window;

    /// Vector aller Hintergrundbilder
    std::vector<QGraphicsPixmapItem> backgrounds;

    /// Vektor der die Darstellgung von Leben,Highscore und Pegel enhält
    std::vector<QGraphicsTextItem> playerStats;

    /// Zeiger auf QApplication
    QApplication *appPointer;
    /// für Zeitmessung
    std::chrono::high_resolution_clock::time_point letzterAufruf;
    /// Erstelle Input Objekt zum Aufzeichnen der Keyboard Inputs
    Input *keyInput = new Input();


    // Menüs
    enum gameState state = gameMenuStart;    /// aktueller Spielzustand
    Menu *aktMenu = menuStart;      /// aktuell aktives Menü, null während das Spiel läuft; wird in setState gesetzt

    Menu *menuStart;
    Menu *menuCredits;
    Menu *menuLevel;
    Menu *menuBreak;
    Menu *menuStatistics;
    Menu *menuName;
    Menu *menuHighscore;
    /// zur Unterscheidung und Identifizierung der Menü-Einträge
    enum menuIds {
        menuId_NonClickable,
        menuStartId_NewGame, menuStartId_EndGame, menuStartId_Credits,   // Startmenü
        menuCreditsId_Back, // Credits
        menuLevelId_Back, menuLevelId_Demo, menuLevelId_Level1, menuLevelId_Level2, menuLevelId_Level3, menuLevelId_StartGame,   // Levelauswahl
        menuBreakId_Resume, menuBreakId_EarlyEnd, menuBreakId_EndGame,    // Pause
        menuStatisticsId_Next,  // Statistik
        menuNameId_Next,        // Name eingeben
        menuHighscoreId_Next   // Highscoretabelle
    };

    /// stepCount wird mit jedem Step um ein erhöht
    /// Auslesen der vergangenen Zeit: stepCount * getStepIntervall()
    int stepCount = 0;
    int audioIDs;
    audioCooldownStruct audioCooldown;
    audioDistanceStruct audioDistance;
    chrono::high_resolution_clock::time_point thisStep;
    chrono::high_resolution_clock::time_point testStep;

};

#endif // GAME_H

