#ifndef RENDERGUIELEMENT_H
#define RENDERGUIELEMENT_H

#include <QGraphicsPixmapItem>

class RenderGuiElement: public QGraphicsPixmapItem{
public:

    //Konstruktor und Destruktor
    RenderGuiElement();
    ~RenderGuiElement();

private:
    //Attribute Grafikelement "GuiElement"
    struct position;
    int type;
    int status;

};

#endif // RENDERGUIELEMENT_H
