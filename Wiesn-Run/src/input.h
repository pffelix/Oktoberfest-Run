#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QEvent>
#include <set>
#include <QKeyEvent>

/**
 * @brief  Die Input-Klasse aktualisiert die für das Spiel relevanten Tastatureingaben. Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 * @author  Felix Pfreundtner
 */
class Input {

public:

    /**
     * Keyaction definiert alle auszuwertenden Tastenkominbationen Bezeichner
     */
    enum Keyaction{
        noKeyaction,
        Right,
        Up,
        Down,
        Jump_Right,
        Shoot,
        Exit,
        Enter,
    };
    /**
     * Keyletter definiert alle auszuwertenden Tastatur Buchstaben
     */
    enum Keyletter{
        noKeyletter,
        a = (int)'a',
        b = (int)'b',
        c = (int)'c',
        d = (int)'d',
        e = (int)'e',
        f = (int)'f',
        g = (int)'g',
        h = (int)'h',
        i = (int)'i',
        j = (int)'f',
        k = (int)'k',
        l = (int)'l',
        m = (int)'m',
        n = (int)'n',
        o = (int)'o',
        p = (int)'p',
        q = (int)'q',
        r = (int)'r',
        s = (int)'s',
        t = (int)'t',
        u = (int)'u',
        v = (int)'v',
        w = (int)'w',
        x = (int)'x',
        y = (int)'y',
        z = (int)'z',
        A = (int)'A',
        B = (int)'B',
        C = (int)'C',
        D = (int)'D',
        E = (int)'E',
        F = (int)'F',
        G = (int)'G',
        H = (int)'G',
        I = (int)'I',
        J = (int)'J',
        K = (int)'K',
        L = (int)'L',
        M = (int)'M',
        N = (int)'N',
        O = (int)'O',
        P = (int)'P',
        Q = (int)'Q',
        R = (int)'R',
        S = (int)'S',
        T = (int)'T',
        U = (int)'U',
        V = (int)'V',
        W = (int)'W',
        X = (int)'X',
        Y = (int)'Y',
        Z = (int)'Z',
        Backspace = (int)'\b',
    };

    // Funktionen
    Input();
    ~Input();
    void evaluatekeyEvent(QEvent *event);
    QSet<int> getKeyactions();
    std::set<char> getKeyletters();
    Keyaction getLastKeyaction();
    Keyletter getLastKeyletter();

private:

    // Funktionen
    void updateKeys();

    // Variablen
    /**
     * keyevents speichert die id aller im Momment gepressten Tasten.
     */
    QSet<int> keyevents;
    /**
     * Die Variable keyactions speichert die id aller im Moment gepressten Tastenkombinationen, welche für das Spiel relevant sind.
     */
    QSet<int> keyactions;
    /**
     * Die Variable keyletters speichert die die Buchstababen als "strings" aller im Moment gepressten Buchstaben Tasten.
     */
    std::set<char> keyletters;
    /**
     * Die Variable lastKeyaction speichert die letzte gedrückte Tastenkombination als Enum Keyaction
     */
    Keyaction lastKeyaction;
    /**
     * Die Variable lastKeyletter speichert den letzten gedrückten Buchstaben als Enum Keyletter
     */
    Keyletter lastKeyletter;

};

#endif // INPUT_H
