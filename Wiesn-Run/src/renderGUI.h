#ifndef RENDERGUI_H
#define RENDERGUI_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>

class RenderGUI {

public:
    //Konstruktor und Destruktor
    RenderGUI(QGraphicsScene *scene);
    ~RenderGUI();

    void setPos(int x);
    void setValues(int health, int ammo, int alcohol, int score);

private:

    QGraphicsTextItem showHealth;
    QGraphicsTextItem showScore;
    QGraphicsTextItem showAmmo;
    QGraphicsTextItem showAlcohol;

};

#endif // RENDERGUI_H
