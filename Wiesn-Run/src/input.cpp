#include "input.h"

/**
 * @brief  Input::Input
 *         Konstruktor instanziert ein Objekt der Klasse Input und installiert den Eventfilter
 * @param  installEventFilter(this)
 * @author  Felix
 */
Input::Input() {
    // this->installEventFilter(this);
    std::cout << "intitialze \n";
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
 *         und speichert die ids in der Instanzvariable keyevents:
 *         wird eine Taste nicht mehr gedrück wird die id in keyevents gelöscht
 *         wird eine Taste neu gedrückt wird die id in keyevents hinzugefügt
 * @param  QObject *obj, QEvent *event
 * @return  Flag
 * @author  Felix
 */
bool Input::eventFilter(QObject *obj, QEvent *event) {
    if(event->type() == QEvent::KeyPress) {
         keyevents += ((QKeyEvent*)event)->key();
         std::cout << "key pressed why";
         return true;
    }
    else if(event->type()==QEvent::KeyRelease) {
        keyevents -= ((QKeyEvent*)event)->key();
        std::cout << "key released";
        return true;
    }
    else {
        return QObject::eventFilter(obj, event);
    }
}


/**
 * @brief  Input::updateKeycomb
 *         updateKeycomb sortiert aus allen in keyevents gespeicherten (im Momemnt
 *         gepressenten Tastatur Eingaben) die für das Spiel relevanten Kombinationen
 *         heraus und aktualisiert die ids in der Instanzvariable keycomb:
 *         wird eine Aktion nicht mehr gedrück wird die id in keycomb gelöscht
 *         wird eine Aktion neu gedrückt wird die id in keycomb hinzugefügt
 * @author  Felix
 */
void Input::updateKeycomb() {
    if(keyevents.contains(Qt::Key_Up) && keyevents.contains(Qt::Key_Right)) {
    //keycomb += "jump_forward";
    }
}

/**
 * @brief  Input::getKeycomb
 *         getKeycomb gibt bei Aufruf die Instanzvariable keycomb zurück
 * @return  Instanzvariable keycomb
 * @author  Felix
 */
QSet<int> Input::getKeycomb() {
    return keycomb;
}
