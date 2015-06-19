#ifndef RENDERPLAYER_H
#define RENDERPLAYER_H

#include <QGraphicsPixmapItem>

class RenderPlayer: public QGraphicsPixmapItem{
public:

    //Konstruktor und Destruktor
    RenderPlayer();
    ~RenderPlayer();

private:
    //Attribute Grafikelement "Player"
    struct position;
    bool attacks;
    bool isDead;
    bool getsDamage;
    bool collectsPowerUp;
    bool jumps;
    bool runs;

};

#endif // RENDERPLAYER_H
