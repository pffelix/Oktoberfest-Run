#include "input.h"

/**
 * @brief  Input::Input
 *         Konstruktor instanziert ein Objekt der Klasse Input.
 * @author  Felix Pfreundtner
 */
Input::Input() {
}


/**
 * @brief  Input::~Input
 *         Destruktor löscht ein Objekt der Klasse Input
 * @author  Felix Pfreundtner
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
 * @return  Boolean
 * @author  Felix Pfreundtner
 */

bool Input::eventFilter(QObject *obj, QEvent *event) {
    if(event->type() == QEvent::KeyPress && ((QKeyEvent*)event)->isAutoRepeat() == false) {
        //qDebug("key pressed");
        keyevents += ((QKeyEvent*)event)->key();
        updateKeys();
        return true;
    }
    else if(event->type() == QEvent::KeyRelease && ((QKeyEvent*)event)->isAutoRepeat() == false) {
        //qDebug("key released");
        keyevents -= ((QKeyEvent*)event)->key();
        updateKeys();
        return true;
        }
    else {
         return QObject::eventFilter(obj, event);
    }
}

/**
 * @brief  Input::updateKeys
 *         updateKeyactions berechnet aus allen in keyevents gespeicherten Tastatureingaben
 *         die für das Spiel relevanten Kombinationen und speichert diese in keyactions.
 *         Jede Aktionen ist im QSet keyactions als Integer gespeichert, welche über die enumeration Keyaction adressiert wird.
 *         Wird durch die Funktion eventFilter ein KeyRelease oder KeyPress Event aufgezeichnet,
 *         so wird der QSet keyactions gelöscht und mit den aktulisierten Werten im Qset keyevents abgeglichen.
 *         Sind Tasten oder Tastenkombinationen gedrück worden, welche für das Spiel relevant sind so wird die zur Aktion
 *         gehörige integer ID im QSet keyactions hinzugefügt.
 * @author  Felix Pfreundtner
 */
void Input::updateKeys() {
    keyactions.clear();
    /// update Keyactions
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
            lastKeyaction = Keyaction::Up;
            qDebug("Up");
    }
    if(keyevents.contains(Qt::Key_Down)) {
            keyactions += Keyaction::Down;
            lastKeyaction = Keyaction::Down;
            qDebug("Down");
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
            lastKeyaction = Keyaction::Exit;
            qDebug("Exit");
    }
    if(keyevents.contains(Qt::Key_Enter) || keyevents.contains(Qt::Key_Return))  {
            keyactions += Keyaction::Enter;
            lastKeyaction = Keyaction::Enter;
            qDebug("Enter");
    }
    /// update Keyletters

}

/**
 * @brief  Input::getKeyactions
 *         getKeyactions gibt bei Aufruf die Instanzvariable keyactions zurück.
 *         Jeder Tastaturkombination wird eine Integer ID zugeordnet welche im QSet keyactions gespeichert ist.
 *         Über die Enumeration Input::Keyaction ist jeder Spielbefehl mit dem zugehörigen Indize in keyactions verknüft.
 *         Möchte man nun bespielsweise abfragen ob der Spieler im Moment schießt so überprüft man:
 *         input->getKeyactions().contains(Input::Keyaction::Shoot) == True.
 * @return Instanzvariable keyactions
 * @author Felix Pfreundtner
 */
QSet<int> Input::getKeyactions() {
    return keyactions;
}

/**
 * @brief  Input::getKeyletters
 *         getKeyletters gibt bei Aufruf die Instanzvariable keyletters zurück.
 *         Jeder Buchststaben Taste wird ein String Buchstaben zugeordner, welcher im QSet keyletters gespeichert ist.
 *         Über die Enumeration Input::Keyletter ist jeder Buchstabe mit dem zugehörigen Indize in keyletters verknüft.
 *         Möchte man nun bespielsweise abfragen ob der Spieler im Moment die "a" Taste drückt so überprüft man:
 *         input->getKeyletters().contains(Input::Keyaction::Shoot) == True.
 * @return Instanzvariable keyactions
 * @author Felix Pfreundtner
 */
QSet<QString> Input::getKeyletters() {
    return keyletters;
}

/**
 * @brief Input::getLastKeyaction
 *        Gibt letzte gedrücke Keyaction Taste zurück und setzt die Variable lastKeyaction auf noKeyaction.
 *        Wird für die Menüführung gebraucht, da ein dauerhaftes Auswerten der Tasten dort zu Sprüngen
 *        beim Auswählen der Menü Einträge führt.
 * @return Enum Keyaction
 * @author Rupert, Felix
 */
Input::Keyaction Input::getLastKeyaction() {
    Keyaction lastKeyaction_return = lastKeyaction;
    lastKeyaction = noKeyaction;
    return lastKeyaction_return;
}

/**
 * @brief Input::getLastKeyletter
 *        Gibt letzte gedrücke Keyletter Taste zurück und setzt die Variable lastKeyletter auf noKeyletter.
 *        Verwendung findet die Funktion beim Eingabe des Highscore Namens.
 * @return Enum Keyletter
 * @author Felix
 */
Input::Keyletter Input::getLastKeyletter() {
    Keyletter lastKeyletter_return = lastKeyletter;
    lastKeyletter = noKeyletter;
    return lastKeyletter_return;
}


