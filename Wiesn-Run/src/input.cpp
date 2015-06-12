#include "input.h"


Input::Input() {
    this->installEventFilter(this);
}

Input::~Input() {

}



bool Input::eventFilter(QEvent *event){
    if(event->type() == QEvent::KeyPress){
         keyevents += ((QKeyEvent*)event)->key();
    }
    if(event->type()==QEvent::KeyRelease){
        keyevents -= ((QKeyEvent*)event)->key();
    }
return false;
}


void Input::updateKeyactions(){
    if(keyevents.contains(Qt::Key_Up) && keyevents.contains(Qt::Key_Right)){
    //keyactions += "jump_forward";
    }

}

QSet<int> Input::getKeyactions(){
    return keyactions;
}
