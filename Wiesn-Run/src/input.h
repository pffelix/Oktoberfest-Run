#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <string>

class Input : public QObject {
public:
    Input();
    ~Input();
    /// getKeyactions returns the variable keyactions
    QSet<int> getKeyactions();
    Q_OBJECT

private:
    /// keyevents contains the id of all currently pressed keyboard buttons
    QSet<int> keyevents;
    /// keyactions contains the specifiers of all currently pressed game relevant keyboard button combinations
    QSet<std::string> keyactions;

    /// generate specifiers for all currently pressed game relevant keyboard button combinations and save in variable keyactions
    void updateKeyactions();

protected:
    /// eventFilter get's the currently presse keyboard buttons
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // INPUT_H
