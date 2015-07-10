#ifndef RENDERGUI_H
#define RENDERGUI_H

#include <QGraphicsTextItem>

class RenderGUI {

public:
    //Konstruktor und Destruktor
    RenderGUI();
    ~RenderGUI();

    void setPos(int x);
    void setValues(int health, int ammo, int alcohol, int score);

        QGraphicsTextItem showHealth;
private:

    QGraphicsTextItem showScore;
    QGraphicsTextItem showAmmo;
    QGraphicsTextItem showAlcohol;

};

#endif // RENDERGUI_H
