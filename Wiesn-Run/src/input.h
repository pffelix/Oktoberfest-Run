#ifndef INPUT_H
#define INPUT_H


#include <QSet>
#include <QObject>
#include <QEvent>
#include <string>

class Input {
public:
    Input();
    ~Input();
    /// getKeyactions returns the variable keyactions
    QSet<int> getKeyactions();

private:
    /// keyevents contains the id of all currently pressed keyboard buttons
    QSet<int> keyevents;
    /// keyactions contains the specifiers of all currently pressed game relevant keyboard button combinations
    QSet<std::string> keyactions;

    /// eventFilter get's the currently presse keyboard buttons
    bool eventFilter(QObject * obj, QEvent * event);
    void updateKeyactions();

};

#endif // INPUT_H
