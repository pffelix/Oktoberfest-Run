#ifndef RENDERGUI_H
#define RENDERGUI_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class RenderGUI {

public:
    //Konstruktor und Destruktor
    RenderGUI(QGraphicsScene *scene);
    ~RenderGUI();

    void setPos(int x);
    void setValues(int health, int alcohol, int ammo, int score);

private:

    QGraphicsTextItem showHealth;
    QGraphicsRectItem showHealthBar;
    QGraphicsTextItem showScore;
    QGraphicsTextItem showAmmo;
    QGraphicsTextItem showAlcohol;
    QGraphicsRectItem showAlcoholBar;

};

#endif // RENDERGUI_H
