#ifndef MENU_H
#define MENU_H

#include <list>
#include <string>
#include "definitions.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QFont>
#include <QString>

/**
 * @brief Klasse zum Erzeugen und Anzeigen von Spielmenüs.
 * Eine Instanz repräsentiert ein Menü, die wichtigsten Funktionen sind folgende:
 *  - Einträge hinzufügen
 *  - aktuelle Auswahl ändern (nach Tastendruck)
 *  - anzeigen
 *
 * Die Interaktion mit dem Benutzer wird nicht in der Klasse behandelt,
 * z.B. werden Tastendrücke in step() interpretiert und entsprechenend changeSelection() aufgerufen.
 *  @author Rupert
 */
class Menu
{


public:

    // --------- Structs und Enums -------------------

    /// Struct zur Beschreibung eines Menü-Eintrags
    struct menuEntry {
        std::string name;   /// Name, der angezeigt wird
        int id; /// ID des Eintrags. Wird mittels menuIds aus game.h eindeutig belegt und in step() zur Unterscheidung der Einträge verwendet.
        int position;   /// Position im Menü. 0=ganz oben, wird automatisch beim Anlegen gesetzt, d.h. die Reihenfolge ist die Reihenfolge, in der die Einträge erzeugt werden, sie kann später nicht mehr geändert werden.
        bool isClickable;   /// true = Eintrag kann ausgewählt werden, Einträge mit false werden in changeSelection() übersprungen.
        bool menuOnEnter;   /// Ob auf diesen Eintrag ein weiteres Menü folgt. true = Dieser EIntrag ruft ein anderes Menü auf, macht die Auswertung in step() einfacher.
        gameState stateOnClick; /// nächstes Menü. Zusammen mit menuOnEnter, wird in step() ausgewertet.
        QGraphicsTextItem showEntry;    /// Representierung in der Grafik
    };

    /// wird von changeSelection benötigt
    enum menuSelectionChange {
        up, down
    };

    /// verschiedene Menü-Typen (für Background-Musik)
    enum menuType {
        normal, highscore
    };

    // ------------ Konstruktor, Destruktor ----------------

    Menu(std::string *menuTitle, menuType type = normal);
    ~Menu();

    // ------------ Öffentliche Methoden -------------------

    // löscht alle Einträge bis auf den Titel
    void clear();

    // gibt den Typ zurück
    menuType getType();

    // gibt den Titel zurück
    std::string *getTitle();

    // Initialisiert das angezeigt Menü
    int displayInit();

    // Aktualisiert das angezeigt Menü
    int displayUpdate();

    // Neuen Eintrag hinzufügen
    int addEntry(std::string name, int id, bool clickable = false, gameState stateOnClick = (gameState)NULL);

    // wird nach Tastendruck aufgerufen
    int changeSelection(menuSelectionChange changeType);

    // Zeiger auf aktuelle gewählten Menüeintrag, sollte nach Enter aufgerufen werden
    Menu::menuEntry *getSelection();

    // Gibt Menü-Eintrag an der entsprechenden Position zurück
    Menu::menuEntry *getEntry(int position);

    // ---------------- Variablen ---------------------

    /// Zeiger auf das Menü-Hintergrundbild
    QGraphicsPixmapItem background;

    /// Zeiger auf die Menü-Scene
    QGraphicsScene * menuScene;

    /// Bierkrug im Menü
    QGraphicsPixmapItem beerMug;

private:

    /// Liste, die die Menü-Einträge enthalt
    std::list<struct menuEntry*> menuEntrys;

    /// Zeiger auf gewählten Menüpunkt
    int currentPosition = 0;

    /// Anzahl der Einträge
    int numberOfEntrys = 0;

    /// Zeiger auf String, in dem der Titel des Menüs steht. Wird automatisch als erster Eintrag angezeigt.
    std::string *title;

    /// Menü-Typ
    menuType type;

    // ersten Eintrag auswählen
    int selectFirstEntry();

};

#endif // MENU_H
