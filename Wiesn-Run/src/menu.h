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
 * @brief Menü-Klasse
 * eine Instanz repräsentiert ein Menü mit diesen Funktionen:
 *  - Einträge hinzufügen
 *  - aktuelle Auswahl ändern (nach Tastendruck)
 *  - anzeigen
 */
class Menu
{


public:


    /// Struct zur Beschreibung eines Menü-Eintrags
    struct menuEntry {
        std::string name;
        int id;
        int position;
        bool isClickable;   // für Highscore-Menü
        void (*handler)();  // Zeiger auf Funktion (Handler für Enter)
        QGraphicsTextItem showEntry;
    };
    /// wird von der Menu-Klasse zur Auswahl-Änderung benötigt
    enum menuSelectionChange {
        up, down, /*enter*/
    };


    Menu(std::string *menuTitle);

    /// gibt den Titel zurück
    std::string *getTitle();

    /// Initialisiert das angezeigt Menü
    int displayInit();

    /// Aktualisiert das angezeigt Menü
    int displayUpdate();

    /// Neuen Eintrag hinzufügen (evtl private -> Einträge nur im Konstruktor erstellen -> unterschiedlich viele Argumente)
    int addEntry(std::string name, int id, bool clickable=false, void (*handlerFunction)()=NULL);

    /// wird nach Tastendruck aufgerufen
    int changeSelection(menuSelectionChange changeType);

    /// Zeiger auf aktuelle gewählten Menüeintrag, sollte nach Enter aufgerufen werden
    Menu::menuEntry *getSelection();

    /// Gibt Menü-Eintrag an der entsprechenden Position zurück
    Menu::menuEntry *getEntry(int position);

    /// Zeiger auf die Menü-Scene und das Menü-Hintergrundbild
    QGraphicsPixmapItem * background;
    QGraphicsScene * menuScene;

private:
    /// Liste, die die Menü-Einträge enthalt
    std::list<struct menuEntry*> menuEntrys;

    /// Zeiger auf gewählten Menüpunkt
    //struct menuEntry *currentSelection;
    int currentPosition = 0;

    /// Anzahl der Einträge
    int numberOfEntrys = 0;

    /// Zeiger auf String, in dem der Titel des Menüs steht
    std::string *title;

};

#endif // MENU_H
