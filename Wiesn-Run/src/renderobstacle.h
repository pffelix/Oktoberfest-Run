#ifndef RENDEROBSTACLE_H
#define RENDEROBSTACLE_H

#include <QGraphicsPixmapItem>

class RenderObstacle: public QGraphicsPixmapItem{
public:

    //Konstruktor und Destruktor
    RenderObstacle();
    ~RenderObstacle();

    //Rendermethode
    void render(int x);

private:
    //Attribute Grafikelement "Obstacle"
    int posX;
    int obstacleType;

};

#endif // RENDEROBSTACLE_H
