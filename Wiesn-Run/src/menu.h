#ifndef MENU_H
#define MENU_H

#include <list>
#include <string>
#include "definitions.h"

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



    Menu();

    /// Zeigt das Menü an
    int display();

    /// Neuen Eintrag hinzufügen (evtl private -> Einträge nur im Konstruktor erstellen -> unterschiedlich viele Argumente)
    int addEntry(std::string name, int id);

    /// wird nach Tastendruck aufgerufen
    int changeSelection(menuSelectionChange changeType);

    /// Zeiger auf aktuelle gewählten Menüeintrag, sollte nach Enter aufgerufen werden
    menuEntry *getSelection();

private:
    /// Liste, die die Menü-Einträge enthalt
    std::list<struct menuEntry*> menuEntrys;

    /// Zeiger auf gewählten Menüpunkt
    struct menuEntry *currentSelection;
    int currentPosition = 0;

    /// Anzahl der Einträge
    int numberOfEntrys = 0;


};

#endif // MENU_H
