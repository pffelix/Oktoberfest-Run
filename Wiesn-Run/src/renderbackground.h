#ifndef RENDERBACKGROUND_H
#define RENDERBACKGROUND_H

#include <QGraphicsPixmapItem>

class RenderBackground: public QGraphicsPixmapItem{
public:

    //Konstruktor und Destruktor
    RenderBackground();
    ~RenderBackground();

private:
    //Attribute Grafikelement "Background"
    int level;
    bool isMoving;

};

#endif // RENDERBACKGROUND_H
