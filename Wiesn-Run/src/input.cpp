#include "input.h"

/**
 * @brief  Konstruktor instanziiert ein Objekt der Klasse Input. Wird einmal zum Spielstart von dem game Objekt aufgerufen und ein Objekt keyInput erstellt.
 * @author  Felix Pfreundtner
 */
Input::Input() {
}


/**
 * @brief  Destruktor löscht ein Objekt der Klasse Input
 * @author  Felix Pfreundtner
 */
Input::~Input() {
}

/**
 * @brief  Nach Aufruf über Game::eventFilter wertet evaluatekeyEvent alle im Momment gleichzeitig gepressten Tastatur Eingaben aus und speichert die zugehörigen enum ids in der Instanzvariable keyevents. Wird eine Taste nicht mehr gedrück wird die enum id in keyevents gelöscht. Wird eine Taste neu gedrückt wird die enum id in keyevents hinzugefügt. Um die relevanten Tastaturkombinationen auszuwerten wird die Methode updateKeys aufgerufen.
 * @param  QEvent *event
 * @author  Felix Pfreundtner
 */

void Input::evaluatekeyEvent(QEvent *event) {
    if(event->type() == QEvent::KeyPress && ((QKeyEvent*)event)->isAutoRepeat() == false) {
        //qDebug("key pressed");
        keyevents += ((QKeyEvent*)event)->key();
        updateKeys();
    }
    else if(event->type() == QEvent::KeyRelease && ((QKeyEvent*)event)->isAutoRepeat() == false) {
        //qDebug("key released");
        keyevents -= ((QKeyEvent*)event)->key();
        updateKeys();
        }
    else if (event->type() == QEvent::Close) {
    }
}

/**
 * @brief  updateKeys berechnet aus allen in keyevents gespeicherten Tastatureingaben die für das Spiel relevanten Kombinationen und speichert diese im QSet keyactions oder set keyletters. Jede aktuell gedrückte Tastaturkombination ist im QSet keyactions als Integer gespeichert, welche über die enumeration Keyaction adressiert wird. Jeder aktuell gedrückte Buchstabe ist im set keyletters als char gespeichert, welche über die enumeration Keyletter und einen int to char Typecast adressiert wird. Wird durch die Methode evaluatekeyEvent ein KeyRelease oder KeyPress Event aufgezeichnet, so nach Aufruf der Methode das QSet keyactions und set keyletters gelöscht. Im Anschluss wird geprüft ob in der neuen Situation in keyevents relevante Tastaturkombinationen vorhanden sind. Sind Tasten oder Tastenkombinationen gedrückt worden, welche für das Spiel relevant sind so wird die zur Aktion gehörige enum Keyaction integer ID im QSet keyactions hinzugefügt. Ist ein Buchstabe in keyevents gespeichert, so wird der zugehörige char im set keyletters gespeichert.
 * @author  Felix Pfreundtner
 */
void Input::updateKeys() {
    // update alle für das Gameplay relevante Tasten(-kombinationen)
    keyactions.clear();
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

    // update für die Tastatureingabe relevante Tasten(-kombinationen)
    keyletters.clear();
    if(keyevents.contains(Qt::Key_A)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::A);
            lastKeyletter = Keyletter::A;
            qDebug("A");
        }
        else {
            keyletters.insert((char)Keyletter::a);
            lastKeyletter = Keyletter::a;
            qDebug("a");
        }
    }
    if(keyevents.contains(Qt::Key_B)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::B);
            lastKeyletter = Keyletter::B;
            qDebug("B");
        }
        else {
            keyletters.insert((char)Keyletter::b);
            lastKeyletter = Keyletter::b;
            qDebug("b");
        }
    }
    if(keyevents.contains(Qt::Key_C)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::C);
            lastKeyletter = Keyletter::C;
            qDebug("C");
        }
        else {
            keyletters.insert((char)Keyletter::c);
            lastKeyletter = Keyletter::c;
            qDebug("c");
        }
    }
    if(keyevents.contains(Qt::Key_D)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::D);
            lastKeyletter = Keyletter::D;
            qDebug("D");
        }
        else {
            keyletters.insert((char)Keyletter::d);
            lastKeyletter = Keyletter::d;
            qDebug("d");
        }
    }
    if(keyevents.contains(Qt::Key_E)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::E);
            lastKeyletter = Keyletter::E;
            qDebug("E");
        }
        else {
            keyletters.insert((char)Keyletter::e);
            lastKeyletter = Keyletter::e;
            qDebug("e");
        }
    }
    if(keyevents.contains(Qt::Key_F)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::F);
            lastKeyletter = Keyletter::F;
            qDebug("F");
        }
        else {
            keyletters.insert((char)Keyletter::f);
            lastKeyletter = Keyletter::f;
            qDebug("f");
        }
    }
    if(keyevents.contains(Qt::Key_G)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::G);
            lastKeyletter = Keyletter::G;
            qDebug("G");
        }
        else {
            keyletters.insert((char)Keyletter::g);
            lastKeyletter = Keyletter::g;
            qDebug("g");
        }
    }
    if(keyevents.contains(Qt::Key_H)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::H);
            lastKeyletter = Keyletter::H;
            qDebug("H");
        }
        else {
            keyletters.insert((char)Keyletter::h);
            lastKeyletter = Keyletter::h;
            qDebug("h");
        }
    }
    if(keyevents.contains(Qt::Key_I)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::I);
            lastKeyletter = Keyletter::I;
            qDebug("I");
        }
        else {
            keyletters.insert((char)Keyletter::i);
            lastKeyletter = Keyletter::i;
            qDebug("i");
        }
    }
    if(keyevents.contains(Qt::Key_J)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::J);
            lastKeyletter = Keyletter::J;
            qDebug("J");
        }
        else {
            keyletters.insert((char)Keyletter::j);
            lastKeyletter = Keyletter::j;
            qDebug("j");
        }
    }
    if(keyevents.contains(Qt::Key_K)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::K);
            lastKeyletter = Keyletter::K;
            qDebug("K");
        }
        else {
            keyletters.insert((char)Keyletter::k);
            lastKeyletter = Keyletter::k;
            qDebug("k");
        }
    }
    if(keyevents.contains(Qt::Key_L)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::L);
            lastKeyletter = Keyletter::L;
            qDebug("L");
        }
        else {
            keyletters.insert((char)Keyletter::l);
            lastKeyletter = Keyletter::l;
            qDebug("l");
        }
    }
    if(keyevents.contains(Qt::Key_M)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::M);
            lastKeyletter = Keyletter::M;
            qDebug("M");
        }
        else {
            keyletters.insert((char)Keyletter::m);
            lastKeyletter = Keyletter::m;
            qDebug("m");
        }
    }
    if(keyevents.contains(Qt::Key_N)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::N);
            lastKeyletter = Keyletter::N;
            qDebug("N");
        }
        else {
            keyletters.insert((char)Keyletter::n);
            lastKeyletter = Keyletter::n;
            qDebug("n");
        }
    }
    if(keyevents.contains(Qt::Key_O)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::O);
            lastKeyletter = Keyletter::O;
            qDebug("O");
        }
        else {
            keyletters.insert((char)Keyletter::o);
            lastKeyletter = Keyletter::o;
            qDebug("o");
        }
    }
    if(keyevents.contains(Qt::Key_P)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::P);
            lastKeyletter = Keyletter::P;
            qDebug("P");
        }
        else {
            keyletters.insert((char)Keyletter::p);
            lastKeyletter = Keyletter::p;
            qDebug("p");
        }
    }
    if(keyevents.contains(Qt::Key_Q)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::Q);
            lastKeyletter = Keyletter::Q;
            qDebug("Q");
        }
        else {
            keyletters.insert((char)Keyletter::q);
            lastKeyletter = Keyletter::q;
            qDebug("q");
        }
    }
    if(keyevents.contains(Qt::Key_R)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::R);
            lastKeyletter = Keyletter::R;
            qDebug("R");
        }
        else {
            keyletters.insert((char)Keyletter::r);
            lastKeyletter = Keyletter::r;
            qDebug("r");
        }
    }
    if(keyevents.contains(Qt::Key_S)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::S);
            lastKeyletter = Keyletter::S;
            qDebug("S");
        }
        else {
            keyletters.insert((char)Keyletter::s);
            lastKeyletter = Keyletter::s;
            qDebug("s");
        }
    }
    if(keyevents.contains(Qt::Key_T)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::T);
            lastKeyletter = Keyletter::T;
            qDebug("T");
        }
        else {
            keyletters.insert((char)Keyletter::t);
            lastKeyletter = Keyletter::t;
            qDebug("t");
        }
    }
    if(keyevents.contains(Qt::Key_U)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::U);
            lastKeyletter = Keyletter::U;
            qDebug("U");
        }
        else {
            keyletters.insert((char)Keyletter::u);
            lastKeyletter = Keyletter::u;
            qDebug("u");
        }
    }
    if(keyevents.contains(Qt::Key_V)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::V);
            lastKeyletter = Keyletter::V;
            qDebug("V");
        }
        else {
            keyletters.insert((char)Keyletter::v);
            lastKeyletter = Keyletter::v;
            qDebug("v");
        }
    }
    if(keyevents.contains(Qt::Key_W)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::W);
            lastKeyletter = Keyletter::W;
            qDebug("W");
        }
        else {
            keyletters.insert((char)Keyletter::w);
            lastKeyletter = Keyletter::w;
            qDebug("w");
        }
    }
    if(keyevents.contains(Qt::Key_X)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::X);
            lastKeyletter = Keyletter::X;
            qDebug("X");
        }
        else {
            keyletters.insert((char)Keyletter::x);
            lastKeyletter = Keyletter::x;
            qDebug("x");
        }
    }
    if(keyevents.contains(Qt::Key_Y)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::Y);
            lastKeyletter = Keyletter::Y;
            qDebug("Y");
        }
        else {
            keyletters.insert((char)Keyletter::y);
            lastKeyletter = Keyletter::y;
            qDebug("y");
        }
    }
    if(keyevents.contains(Qt::Key_Z)) {
        if(keyevents.contains(Qt::Key_Shift)) {
            keyletters.insert((char)Keyletter::Z);
            lastKeyletter = Keyletter::Z;
            qDebug("Z");
        }
        else {
            keyletters.insert((char)Keyletter::z);
            lastKeyletter = Keyletter::z;
            qDebug("z");
        }
    }
    if(keyevents.contains(Qt::Key_Backspace))  {
            keyletters.insert((char)Keyletter::Backspace);
            lastKeyletter = Keyletter::Backspace;
            qDebug("Backspace");
    }
}

/**
 * @brief  getKeyactions gibt bei Aufruf das QSet keyactions zurück, welches alle im Moment gedrückten Spielaktionen als Enum beinhaltet. Jeder Tastaturkombination wird eine Integer ID zugeordnet welche im QSet keyactions gespeichert ist. Über die Enumeration Input::Keyaction ist jeder Spielbefehl mit dem zugehörigen Index in keyactions verknüft. Möchte man nun bespielsweise abfragen ob der Spieler im Moment schießt so überprüft man: input->getKeyactions().contains(Input::Keyaction::Shoot) == True.
 * @return  QSet<int> Instanzvariable keyactions
 * @author  Felix Pfreundtner
 */
QSet<int> Input::getKeyactions() {
    return keyactions;
}

/**
 * @brief  getKeyletters gibt bei Aufruf das set keyletters zurück, welches alle im Moment gedrückten Buchstaben als Enum beinhaltet. Jeder Buchststaben Taste wird ein String Buchstaben zugeordnet, welcher im set keyletters gespeichert ist. Über die Enumeration Input::Keyletter ist jeder Buchstabe mit dem zugehörigen Index in keyletters verknüft.
 * @return  std::set<char> Instanzvariable keyletters
 * @author  Felix Pfreundtner
 */
std::set<char> Input::getKeyletters() {
    return keyletters;
}

/**
 * @brief  Gibt die letzte gedrücke Spielaktion als Enum Keyaction zurück und setzt die Variable lastKeyaction auf noKeyaction. Wird für die Menüführung gebraucht, da ein dauerhaftes Auswerten der Tasten dort zu Sprüngen beim Auswählen der Menü Einträge führt.
 * @return  Enum Keyaction Instanzvariable lastKeyaction
 * @author  Rupert, Felix
 */
Input::Keyaction Input::getLastKeyaction() {
    Keyaction lastKeyaction_return = lastKeyaction;
    lastKeyaction = noKeyaction;
    return lastKeyaction_return;
}

/**
 * @brief  Gibt letzten gedrücken Buchstaben als enum Keyletter zurück und setzt die Variable lastKeyletter auf noKeyletter. Wurde eine Taste gedrückt (lastKeyletter_return != noKeyletter) so kann aus dem Enum Keyletter über eine Typenumwandlung der zugehörige Char berechnet werden: a = (char)lastKeyletter_return. Verwendung findet die Methode bei der Eingabe des Highscore Namens.
 * @return  Enum Keyletter Instanzvariable lastKeyletter
 * @author  Felix
 */
Input::Keyletter Input::getLastKeyletter() {
    Keyletter lastKeyletter_return = lastKeyletter;
    lastKeyletter = noKeyletter;
    return lastKeyletter_return;
}


