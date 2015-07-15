#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QEvent>
#include <set>
#include <QKeyEvent>

/**
 * @brief  Die Input-Klasse aktualisiert die für das Spiel relevanten Tastatureingaben. Eine Instanz keyInput dieser Klasse wird zum Programmstart im game Objekt angelegt. Im Ojekt der Game Klasse wird über die Methode eventFilter() ein QEvent Filter installiert. Dieser ruft bei neuen Events die Methode evaluatekeyEvent() auf, welche prüft ob das Event ein KeyEvent war. Ist dies der Fall wird die aktuelle Tastatureingabe als zusätzlicher Enum in dem QSet keyevents gespeichert oder bei Loslassen der Taste gelöscht. Im Anschluss wird über die Methode updateKeys() überprüft ob mit allen aktuell gedrückten Eingaben (gespeichert in keyevents) eine Tastaturkombination erfolgt, welche für das Spiel relevant ist. Ist dies der Fall wird die aktuelle Tastatureingabe-Aktion als enum Keyaction in dem QSet keyactions gespeichert. Sind Buchstaben in keyevents gespeichert so werden diese im std::set keyletters als char gespeichert. Das Game Objekt kann über die Methoden getKeyactions(), getKeyletters(), getLastKeyaction() und getLastKeyletter()alle, für das Spiel relevanten, Eingaben aus den Variablen auslesen.
 *
 * @author  Felix Pfreundtner
 */
class Input {

public:

    /**
     * @var  enum Keyaction
     * @brief  Keyaction definiert alle auszuwertenden Tastenkominbationen
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
     * @var  enum Keyletter
     * @brief  Keyletter definiert alle auszuwertenden Tastatur Buchstaben
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

    // Methoden
    Input();
    ~Input();
    void evaluatekeyEvent(QEvent *event);
    QSet<int> getKeyactions();
    std::set<char> getKeyletters();
    Keyaction getLastKeyaction();
    Keyletter getLastKeyletter();

private:

    // Methoden
    void updateKeys();

    // Variablen
    /**
     * @var  QSet<int> keyevents
     * @brief  keyevents speichert die id aller im Momment gepressten Tasten.
     */
    QSet<int> keyevents;
    /**
     * @var  QSet<int> keyactions
     * @brief  Die Variable keyactions speichert die id aller im Moment gepressten Tastenkombinationen, welche für das Spiel relevant sind.
     */
    QSet<int> keyactions;
    /**
     * @var  std::set<char> keyletters
     * @brief  Die Variable keyletters speichert die Buchstaben als char aller im Moment gepressten Buchstaben Tasten.
     */
    std::set<char> keyletters;
    /**
     * @var  Keyaction lastKeyaction
     * @brief  Die Variable lastKeyaction speichert die letzte gedrückte Tastenkombination als Enum Keyaction
     */
    Keyaction lastKeyaction;
    /**
     * @var  Keyletter lastKeyletter
     * @brief  Die Variable lastKeyletter speichert den letzten gedrückten Buchstaben als Enum Keyletter
     */
    Keyletter lastKeyletter;

};

#endif // INPUT_H
