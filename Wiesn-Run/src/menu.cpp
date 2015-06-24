#include "menu.h"
#include <QDebug>

/**
 * @brief Menu-Konstruktor
 * @param Zeiger auf String mit Menu-Titel
 * @author Rupert
 */
Menu::Menu(std::string *menuTitle)
{
    title = menuTitle;

}

/**
 * @brief gibt den Menü-Titel zurück
 * @return Zeiger auf String
 * @author Rupert
 */
std::string *Menu::getTitle() {
    return title;
}

/**
 * @brief Initialisiert das sichtbare Menü , muss immer nach anlegen der Menü Entrys aufgerufen werden
 * @return 0 bei Erfolg
 * @author Flo
 */
int Menu::displayInit() {
    //qDebug("%s - %s",getTitle()->c_str(),getSelection()->name.c_str());

    //Menü-Scene und Menü-Hintergrundbild werde initialisiert
    menuScene = new QGraphicsScene;
    background = new QGraphicsPixmapItem(QPixmap(":/images/images/menubackground.png"));
    menuScene->addItem(background);

    //für jeden Menüeintrag wird ein QGraphicsTexItem angelegt, eingestellt und angezeigt
    for(std::list<menuEntry*>::iterator it = menuEntrys.begin(); it != menuEntrys.end(); ++it) {
        //QGraphicsTextItem  * showEntry = new QGraphicsTextItem;
        (*it)->showEntry.setPlainText(QString::fromStdString((*it)->name));
        (*it)->showEntry.setPos(320,300 + 80*(*it)->position );
        (*it)->showEntry.setDefaultTextColor(Qt::blue);
        (*it)->showEntry.setFont(QFont("Times",50));
        menuScene->addItem(&(*it)->showEntry);
    }
    return 0;
}

/**
 * @brief aktualisiert das sichtbare Menü
 * @return 0 bei Erfolg
 * @author Flo
 */
int Menu::displayUpdate() {

    //setzt alle Menüeinträge auf das Defaultaussehen
    for(std::list<menuEntry*>::iterator it = menuEntrys.begin(); it != menuEntrys.end(); ++it) {
        (*it)->showEntry.setDefaultTextColor(Qt::blue);
        (*it)->showEntry.setFont(QFont("Times",50));
    }

    //färbt die aktuelle Selektion Rot ein
    getSelection()->showEntry.setDefaultTextColor(Qt::red);
    getSelection()->showEntry.setFont(QFont("Times",60));
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

        //qDebug("menuUpTry");
            if(currentPosition > 0) {
                currentPosition--;
                //qDebug("menuUp");
            }
            break;
        case menuSelectionChange::down:

        //qDebug("menuDownTry");
            if(currentPosition < numberOfEntrys - 1) {
                currentPosition++;
                //qDebug("menuDown");
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
struct Menu::menuEntry *Menu::getSelection() {
    using namespace std;               // für std::list
    list<menuEntry*>::iterator it;     // Iterator erstellen
    /// Schleife startet beim ersten Element und geht bis zum letzen Element durch
    for(it = menuEntrys.begin(); it != menuEntrys.end(); ++it) {
        menuEntry *aktEntry = *it;
        if(aktEntry->position == currentPosition) {
            return aktEntry;
        }
    }
    qDebug("ERROR | Menu::getSelection(): menuEntry not found");
    return NULL;
}
