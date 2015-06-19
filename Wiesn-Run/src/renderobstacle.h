#ifndef RENDEROBSTACLE_H
#define RENDEROBSTACLE_H

#include <QGraphicsPixmapItem>

class RenderObstacle: public QGraphicsPixmapItem{
public:

    //Konstruktor und Destruktor
    RenderObstacle();
    ~RenderObstacle();

private:
    //Attribute Grafikelement "Obstacle"
    struct position;
    int obstacleType;

};

#endif // RENDEROBSTACLE_H
