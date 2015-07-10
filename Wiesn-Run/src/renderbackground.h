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

    void setPos(int x, QGraphicsPixmapItem *background);
    void updateParallaxe(int x);
    void updateBackgroundPos(int x);

private:
    QGraphicsPixmapItem backgroundOne;
    QGraphicsPixmapItem backgroundTwo;
    QGraphicsPixmapItem backgroundThree;
    QGraphicsPixmapItem backgroundFour;

    int imageLength = 2560;
};

#endif // RENDERBACKGROUND_H
