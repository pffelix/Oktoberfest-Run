#ifndef RENDERENEMY_H
#define RENDERENEMY_H

#include <QGraphicsPixmapItem>

class RenderEnemy: public QGraphicsPixmapItem{
public:

    //Konstruktor und Destruktor
    RenderEnemy();
    ~RenderEnemy();

    //Rendermethode
    void render(int x);

private:
    //Attribute Grafikelement "Enemy"
    int posX;
    bool attacks;
    bool isDead;
    bool getsDamage;
    bool runs;
    int enemyType;

};

#endif // RENDERENEMY_H
