#include "input.h"

/**
 * @brief  Input::Input
 *         Konstruktor instanziert ein Objekt der Klasse Input und installiert den Eventfilter
 * @param  installEventFilter(this)
 * @author  Felix
 */
Input::Input() {
}


/**
 * @brief  Input::~Input
 *         Destruktor löscht ein Objekt der Klasse Input
 * @author  Felix
 */
Input::~Input() {
}

/**
 * @brief  Input::eventFilter
 *         eventFilter sammelt alle im Momment gepressten Tastatur Eingaben
 *         und speichert die integer IDs in der Instanzvariable keyevents.
 *         wird eine Taste nicht mehr gedrück wird die id in keyevents gelöscht
 *         wird eine Taste neu gedrückt wird die id in keyevents hinzugefügt
 * @param  QObject *obj, QEvent *event
 * @return  Flag
 * @author  Felix
 */

bool Input::eventFilter(QObject *obj, QEvent *event) {
    if(event->type() == QEvent::KeyPress && ((QKeyEvent*)event)->isAutoRepeat() == false) {
        //qDebug("key pressed");
        keyevents += ((QKeyEvent*)event)->key();
        updateKeyactions();
        return true;
    }
    else if(event->type() == QEvent::KeyRelease && ((QKeyEvent*)event)->isAutoRepeat() == false) {
        //qDebug("key released");
        keyevents -= ((QKeyEvent*)event)->key();
        updateKeyactions();
        return true;
        }
    else {
         return QObject::eventFilter(obj, event);
    }
}

/**
 * @brief  Input::updateKeyactions
 *         updateKeyactions berechnet aus allen in keyevents gespeicherten Tastatureingaben
 *         die für das Spiel relevanten Kombinationen und speichert diese in keyactions.
 *         Jede Aktionen ist im QSet keyactions als Integer gespeichert, welche über die enumeration Keyaction adressiert wird.
 *         Wird durch die Funktion eventFilter ein KeyRelease oder KeyPress Event aufgezeichnet,
 *         so wird der QSet keyactions gelöscht und mit den aktulisierten Werten im Qset keyevents abgeglichen.
 *         Sind Tasten oder Tastenkombinationen gedrück worden, welche für das Spiel relevant sind so wird die zur Aktion
 *         gehörige integer ID im QSet keyactions hinzugefügt.
 * @author  Felix
 */
void Input::updateKeyactions() {
    keyactions.clear();
    if(keyevents.contains(Qt::Key_Left)) {
            keyactions += Keyaction::Left;
            qDebug("Left");
    }
    if(keyevents.contains(Qt::Key_Right)) {
            keyactions += Keyaction::Right;
            qDebug("Right");
    }
    if(keyevents.contains(Qt::Key_Up)) {
            keyactions += Keyaction::Up;
            qDebug("Up");
    }
    if(keyevents.contains(Qt::Key_Down)) {
            keyactions += Keyaction::Down;
            qDebug("Down");
    }
    if(keyevents.contains(Qt::Key_Left) && keyevents.contains(Qt::Key_Up)) {
            keyactions += Keyaction::Jump_Left;
            qDebug("Jump_Left");
    }
    if(keyevents.contains(Qt::Key_Right) && keyevents.contains(Qt::Key_Up)) {
            keyactions += Keyaction::Jump_Right;
            qDebug("Jump_Right");
    }
    if(keyevents.contains(Qt::Key_Space)) {
            keyactions += Keyaction::Shoot;
            qDebug("Shoot");
    }
    if(keyevents.contains(Qt::Key_Escape)) {
            keyactions += Keyaction::Exit;
            qDebug("Exit");
    }
    if(keyevents.contains(Qt::Key_Enter) || keyevents.contains(Qt::Key_Return))  {
            keyactions += Keyaction::Enter;
            qDebug("Enter");
    }
}

/**
 * @brief  Input::getKeyactions
 *         getKeyactions gibt bei Aufruf die Instanzvariable keyactions zurück.
 *         Jede Tastaturkombination besitzt eine Integer ID welche im QSet keyactions gespeichert ist.
 *         Die IDs sind über die Enumeration Input::Keyaction mit lesbaren Spielbefehlen verknüpft.
 *         Möchte man nun bespielsweise abfragen ob der Spieler im Moment schießt so überprüft man:
 *         input->getKeyactions().contains(Input::Keyaction::Shoot) == True.
 * @return Instanzvariable keyactions
 * @author Felix
 */
QSet<int> Input::getKeyactions() {
    return keyactions;
}

