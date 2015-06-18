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
    enum Keyaction{
        Left = 0,
        Right = 1,
        Up = 2,
        Down = 3,
        Jump_Left = 4,
        Jump_Right = 5,
        Shoot = 6,
        Exit = 7,
        Enter = 8
    };

    Input();
    ~Input();
    QSet<int> getKeyactions();

private:
    /**
     * @brief  keyevents
     *         keyevents speichert die id aller im Momment gepressten Tasten.
     * @author  Felix
     */
    QSet<int> keyevents;
    /**
     * @brief  keyactions
     *         Die Variable keyactions speichert die id aller im Moment
     *         gepressten Tastenkombinationen, welche für das Spiel relevant sind.
     * @author  Felix
     */
    QSet<int> keyactions;


    void updateKeyactions();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // INPUT_H
