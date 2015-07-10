#ifndef RENDERBACKGROUND_H
#define RENDERBACKGROUND_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class RenderBackground
{
public:
    //Konstruktor und Destruktor
    RenderBackground(QGraphicsScene *scene);
    ~RenderBackground();

    QGraphicsPixmapItem backgroundOne;
    QGraphicsPixmapItem backgroundTwo;
    QGraphicsPixmapItem backgroundThree;
    QGraphicsPixmapItem backgroundFour;
};

#endif // RENDERBACKGROUND_H
