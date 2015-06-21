#include "menu.h"
#include <QDebug>

Menu::Menu()
{

}

/**
 * @brief stellt das Menü dar
 * ruft Grafikfunktionen auf
 * @return 0 bei Erfolg
 * @author Rupert
 */
int Menu::display() {
    qDebug("Menü - Eintrag %s aktiv, wähle mit Pfeiltasten",getSelection()->name.c_str());
    return 0;
}


/**
 * @brief Neuen Eintrag hinzufügen
 * @param name String, der angezeigt wird
 * @param id zur eindeutigen Identifizierung, kann zB aus enum gecastet werden
 * @return 0 bei Erfolg
 * @author Rupert
 */
int Menu::addEntry(std::string name, int id) {
    struct menuEntry *entry = new menuEntry;
    entry->id = id;
    entry->name = name;
    entry->position = numberOfEntrys;
    numberOfEntrys++;
    menuEntrys.push_back(entry);
    return 0;
}

/**
 * @brief wird nach Tastendruck aufgerufen
 * @param changeType entweder up oder down
 * @return neue Position
 * @author Rupert
 */
int Menu::changeSelection(enum menuSelectionChange changeType) {
    switch(changeType) {
        case menuSelectionChange::up:

        qDebug("menuUpTry");
            if(currentPosition > 0) {
                currentPosition--;
                qDebug("menuUp");
            }
            break;
        case menuSelectionChange::down:

        qDebug("menuDownTry");
            if(currentPosition < numberOfEntrys - 1) {
                currentPosition++;
                qDebug("menuDown");
            }
            break;
    }
    return currentPosition;
}

/**
 * @brief gibt den gewählten Eintrag zurück
 * sollte nach Enter aufgerufen werden
 * @return Zeiger auf menuEntry des aktuellen Eintrags, NULL bei Fehler
 * @author Rupert
 */
struct menuEntry *Menu::getSelection() {
    using namespace std;               // für std::list
    list<menuEntry*>::iterator it;     // Iterator erstellen
    /// Schleife startet beim ersten Element und geht bis zum letzen Element durch
    for(it = menuEntrys.begin(); it != menuEntrys.end(); ++it) {
        menuEntry *aktEntry = *it;
        if(aktEntry->position == currentPosition) {
            return aktEntry;
        }
    }
    qDebug("menuEntry not found");
    return NULL;
}
