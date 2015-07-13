#include "menu.h"
#include "definitions.h"
#include <QDebug>

/**
 * @brief Konstruktor:
 * Erzeugt ein neues Menü, Titel und Type werden festgelegt.
 * Danch können Einträge hinzugefügt werden.
 * @param menuTitle Zeiger auf String mit Menu-Titel
 * @param type normal/highscore, für Hintergrundmusik
 */
Menu::Menu(std::string *menuTitle, menuType type) {
    title = menuTitle;
    this->type = type;
    this->addEntry(*menuTitle,0,false);
}

/**
 * @brief Menu-Destruktor:
 * Gibt verwendeten Heap-Speicher frei
 */
Menu::~Menu() {
    clear();
    delete menuScene;
}

/**
 * @brief entfernt alle Einträge aus dem Menü außer den Titel.
 * Wird für Statistik und Highscore benötigt, nur so können Menüeinträge verändert werden
 */
void Menu::clear() {
    // jeden Menüeintrag außer den ersten löschen und Speicher freigeben
    while(menuEntrys.size() > 1) {
        menuEntrys.pop_back();
    }
    numberOfEntrys = 1;
    selectFirstEntry();
}

/**
 * @brief gibt den Menü-Typ zurück
 * normal/highscore
 * @return enum menuType
 */
Menu::menuType Menu::getType() {
    return type;
}

/**
 * @brief gibt den Menü-Titel zurück
 * @return Zeiger auf std::tring
 */
std::string *Menu::getTitle() {
    return title;
}


/**
 * @brief Initialisiert das sichtbare Menü.
 * Muss immer nach anlegen der Menü Entrys aufgerufen werden.
 * Jeder Menüeintrag hat auch QGraphicsTextItem welches hier eingestellt entsprechend eingestellt wird
 * @return 0 bei Erfolg
 * @author Flo
 */
int Menu::displayInit() {
    //Menü-Scene und Menü-Hintergrundbild werde initialisiert
    menuScene = new QGraphicsScene;
    background.setPixmap(QPixmap(":/images/images/menubackground.png"));
    menuScene->addItem(&background);

    //Bierkruggrafik welcher die aktuelle Selektion im Menü anzeigt
    beerMug.setPixmap(QPixmap(":/images/images/beer.png"));
    menuScene->addItem(&beerMug);

    //für jeden Menüeintrag wird ein QGraphicsTexItem angelegt, eingestellt und angezeigt
    for(std::list<menuEntry*>::iterator it = menuEntrys.begin(); it != menuEntrys.end(); it ++) {
        (*it)->showEntry.setPlainText(QString::fromStdString((*it)->name));

        if((*it)->position == 0) {
            (*it)->showEntry.setPos(310,150);
            (*it)->showEntry.setDefaultTextColor(Qt::darkBlue);
            (*it)->showEntry.setFont(QFont("Times",60,66));
        }
        else {
            (*it)->showEntry.setPos(310,200 + 80*(*it)->position );
            (*it)->showEntry.setDefaultTextColor(Qt::darkBlue);
            (*it)->showEntry.setFont(QFont("Times",50));
        }
        menuScene->addItem(&(*it)->showEntry);
    }
    return 0;
}

/**
 * @brief aktualisiert das sichtbare Menü.
 * Je nach Userinput wird immer der aktuell ausgewählte Menüeintrag rot dargestellt und der Bierkrug wird links daneben angezeigt.
 * @return 0 bei Erfolg
 * @author Flo
 */
int Menu::displayUpdate() {

    //setzt alle Menüeinträge auf das Defaultaussehen
    for(std::list<menuEntry*>::iterator it = menuEntrys.begin(); it != menuEntrys.end(); ++it) {
         if((*it)->isClickable) {
            (*it)->showEntry.setDefaultTextColor(Qt::darkBlue);
            (*it)->showEntry.setFont(QFont("Times",50));
         }
    }

    // färbt die aktuelle Selektion Rot ein
    getSelection()->showEntry.setDefaultTextColor(Qt::red);
    getSelection()->showEntry.setFont(QFont("Times",50,75,false));

    //Bierkrug neben aktueller Selektion
    beerMug.setPos(260,225 + 80*getSelection()->position);

    return 0;
}

/**
 * @brief Neuen Eintrag hinzufügen
 * @param name String, der angezeigt wird
 * @param id zur eindeutigen Identifizierung, kann zB aus enum menuIds gecastet werden
 * @param clickable Einträg auswählbar?
 * @param stateOnClick nächstes Menü
 *
 * Legt einen neuen menuEntry an und speichert darin die Informationen
 * @return 0 bei Erfolg
 */
int Menu::addEntry(std::string name, int id, bool clickable, gameState stateOnClick) {

    struct menuEntry *entry = new menuEntry;

    entry->id = id;
    entry->name = name;
    entry->position = numberOfEntrys;
    entry->isClickable = clickable;
    entry->stateOnClick = stateOnClick;
    if(stateOnClick != (gameState)NULL) {   // Folgt ein weiteres Menü? Ansonsten ist stateOnClick wertlos
        entry->menuOnEnter = true;
    } else {
        entry->menuOnEnter = false;
    }

    numberOfEntrys++;
    menuEntrys.push_back(entry);
    selectFirstEntry();
    return 0;
}

/**
 * @brief wird nach Tastendruck aufgerufen
 * @param changeType up/down
 * @return 0 bei Erfolg, -1 wenn kein klickbarer Eintrag gefunden
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
 */
struct Menu::menuEntry *Menu::getSelection() {
    return getEntry(currentPosition);
}

/**
 * @brief gibt Eintrag an der gesuchten Position zurück
 * @param position
 * @return Zeiger auf gefundenen Eintrag, sonst NULL
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

/**
 * @brief aktiviert ersten klickbaren Eintrag
 * @return int 0 bei Erfolg, -1 sonst
 */
int Menu::selectFirstEntry() {
    int tmpPos = 0;
    while (tmpPos < numberOfEntrys) {
        menuEntry *entry = getEntry(tmpPos);
        if(entry->isClickable) {
            currentPosition = tmpPos;
            return 0;
        } else {
            tmpPos++;
        }
    }
    // keinen Eintrag gefunden
    return -1;
}

