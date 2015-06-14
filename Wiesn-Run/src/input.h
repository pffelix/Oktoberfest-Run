#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>

/**
 * @brief  Input-Klasse
 *         Die Input-Klasse aktulisiert die für das Spiel releventanten Tastatureingaben.
 *         Eine Instanz dieser Klasse wir innerhalb der game.h angelegt.
 *         Die einzelnen Methoden werden in der input.cpp erklärt.
 * @author  Felix
 */
class Input : public QObject {
public:

    Input();
    ~Input();
    QSet<int> getKeycomb();
    //Q_OBJECT

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
    bool eventFilter(QEvent *event); //QObject *obj
};

#endif // INPUT_H
