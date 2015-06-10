#include "input.h"

Input::Input() {

    this->installEventFilter(this);
}


QSet<int> Input::getKeyactions();


bool Input::eventFilter(QObject * obj, QEvent * event);
void Input::updateKeyactions();
