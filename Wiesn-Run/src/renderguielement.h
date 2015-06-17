#ifndef RENDERGUIELEMENT_H
#define RENDERGUIELEMENT_H

class RenderGuiElement {
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
