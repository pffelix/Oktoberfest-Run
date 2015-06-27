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
    this->addEntry(*menuTitle,0,false);
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
int Menu::addEntry(std::string name, int id, bool clickable) {
    struct menuEntry *entry = new menuEntry;
    entry->id = id;
    entry->name = name;
    entry->position = numberOfEntrys;
    entry->isClickable = clickable;
    numberOfEntrys++;
    menuEntrys.push_back(entry);

    return 0;
}

/**
 * @brief wird nach Tastendruck aufgerufen
 * @param changeType entweder up oder down
 * @return 0 bei Erfolg, -1 wenn kein klickbarer Eintrag vorhanden
 * @author Rupert
 */
int Menu::changeSelection(enum menuSelectionChange changeType) {
    switch(changeType) {
        case menuSelectionChange::up:
            if(currentPosition > 0) {   // noch nicht ganz oben
                // finde nächsten klickbaren Eintrag
                int tmpPos = currentPosition - 1;
                while (tmpPos >= 0) {
                    menuEntry *entry = getEntry(tmpPos);
                    if(entry->isClickable) {
                        currentPosition = tmpPos;
                        return 0;
                    }
                    tmpPos--;
                }
                // keinen Eintrag gefunden
                return -1;
            } else {
                return -1;
            }
            break;
        case menuSelectionChange::down:
            if(currentPosition < numberOfEntrys - 1) {
                // finde nächsten klickbaren Eintrag
                int tmpPos = currentPosition + 1;
                while (tmpPos <= numberOfEntrys - 1) {
                    menuEntry *entry = getEntry(tmpPos);
                    if(entry->isClickable) {
                        currentPosition = tmpPos;
                        return 0;
                    }
                    tmpPos++;
                }
                // keinen Eintrag gefunden
                return -1;
            } else {
                return -1;
            }
            break;
    }
    return 0;
}

/**
 * @brief gibt den gewählten Eintrag zurück
 * sollte nach Enter aufgerufen werden
 * @return Zeiger auf menuEntry des aktuellen Eintrags, NULL bei Fehler
 * @author Rupert
 */
struct Menu::menuEntry *Menu::getSelection() {
    return getEntry(currentPosition);
}

/**
 * @brief gibt Eintrag an der gesuchten Position zurück
 * @param position
 * @return Zeiger auf gefundenen Eintrag, sonst NULL
 * @author Rupert
 */
struct Menu::menuEntry *Menu::getEntry(int position) {
    using namespace std;               // für std::list
    list<menuEntry*>::iterator it;     // Iterator erstellen
    /// Schleife startet beim ersten Element und geht bis zum letzen Element durch
    for(it = menuEntrys.begin(); it != menuEntrys.end(); ++it) {
        menuEntry *aktEntry = *it;
        if(aktEntry->position == position) {
            return aktEntry;
        }
    }
    qDebug("ERROR | Menu::getEntry(): menuEntry not found");
    return NULL;
}
