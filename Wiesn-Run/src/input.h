#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QObject>
#include <QEvent>
#include <QString>
#include <QKeyEvent>

/**
 * @brief  Input-Klasse
 *         Die Input-Klasse aktualisiert die für das Spiel relevanten Tastatureingaben.
 *         Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 *         Die einzelnen Methoden werden in der input.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class Input : public QObject {
    Q_OBJECT

public:
    enum Keyaction{
        noKeyaction,
        Left,
        Right,
        Up,
        Down,
        Jump_Right,
        Shoot,
        Exit,
        Enter,
    };

    enum Keyletter{
        noKeyletter,
        a,
        b,
        c,
        d,
        e,
        f,
        g,
        h,
        i,
        j,
        k,
        l,
        m,
        n,
        o,
        p,
        q,
        r,
        s,
        t,
        u,
        v,
        w,
        x,
        y,
        z,
    };


    Input();
    ~Input();
    QSet<int> getKeyactions();
    QSet<QString> getKeyletters();
    Keyaction getLastKeyaction();
    Keyletter getLastKeyletter();

private:
    /**
     * @brief  keyevents
     *         keyevents speichert die id aller im Momment gepressten Tasten.
     * @author  Felix Pfreundtner
     */
    QSet<int> keyevents;
    /**
     * @brief  keyactions
     *         Die Variable keyactions speichert die id aller im Moment
     *         gepressten Tastenkombinationen, welche für das Spiel relevant sind.
     * @author  Felix Pfreundtner
     */
    QSet<int> keyactions;
    /**
     * @brief  keyletters
     *         Die Variable keyletters speichert die die Buchstababen als "strings" aller im Moment
     *         gepressten Buchstaben Tasten.
     * @author  Felix Pfreundtner
     */
    QSet<QString> keyletters;
    Keyaction lastKeyaction;
    Keyletter lastKeyletter;

    void updateKeys();



protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // INPUT_H
