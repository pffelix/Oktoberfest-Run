#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QString>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <iostream>

/**
 * @brief  Input-Klasse
 *         Die Input-Klasse aktulisiert die für das Spiel releventanten Tastatureingaben.
 *         Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 *         Die einzelnen Methoden werden in der input.cpp erklärt.
 * @author  Felix
 */
class Input : public QObject {
    Q_OBJECT

public:
    enum key{
        left = 0,
        right = 1,
        up = 2,
        down = 3,
        jump_left = 4,
        jump_right = 5,
        jump_up = 6,
        fire = 7,
        exit = 8
    };

    Input();
    ~Input();
    QSet<int> getKeycomb();

private:
    /**
     * @brief  keyevents
     *         keyevents speichert die id aller im Momment gepressten Tasten.
     * @author  Felix
     */
    QSet<int> keyevents;
    /**
     * @brief  keycomb
     *         Die Variable keycomb speichert die id aller im Moment
     *         gepressten Tastenkombinationen, welche für das Spiel relevant sind.
     * @author  Felix
     */
    QSet<int> keycomb;


    void updateKeycomb();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // INPUT_H
