#ifndef RENDERATTACK_H
#define RENDERATTACK_H

#include <QGraphicsPixmapItem>

class RenderAttack: public QGraphicsPixmapItem{
public:
    //Konstruktor und Destruktor
    RenderAttack();
    ~RenderAttack();

private:
    //Attribute Grafikelement "Attack"
    struct position;
    int attackType;

};

#endif // RENDERATTACK_H
