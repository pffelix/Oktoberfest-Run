#ifndef RENDERENEMY_H
#define RENDERENEMY_H

#include <QGraphicsPixmapItem>

class RenderEnemy: public QGraphicsPixmapItem{
public:

    //Konstruktor und Destruktor
    RenderEnemy();
    ~RenderEnemy();

private:
    //Attribute Grafikelement "Enemy"
    struct postion;
    bool attacks;
    bool isDead;
    bool getsDamage;
    bool runs;
    int enemyType;

};

#endif // RENDERENEMY_H
