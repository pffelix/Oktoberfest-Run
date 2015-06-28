#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>

/**
 * @brief  Input-Klasse
 *         Die Input-Klasse aktulisiert die für das Spiel relevanten Tastatureingaben.
 *         Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 *         Die einzelnen Methoden werden in der input.cpp erklärt.
 * @author  Felix Pfreundtner
 */
class Input : public QObject {
    Q_OBJECT

public:
    enum Keyaction{
        noKey,  // Rupert
        Left,
        Right,
        Up,
        Down,
        Jump_Right,
        Shoot,
        Exit,
        Enter,
    };

    Input();
    ~Input();
    QSet<int> getKeyactions();

    Keyaction getAndDeleteLastKey();    // Rupert

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

    void updateKeyactions();

    Keyaction lastKey;      // Rupert

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // INPUT_H
