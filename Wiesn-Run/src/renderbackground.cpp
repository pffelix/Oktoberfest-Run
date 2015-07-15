#include "renderbackground.h"

#include <QGraphicsScene>
#include <math.h>       /* sin,cos */

#define PI 3.14159265

/**
 * @brief Konstruktor für alle Hintergrundgrafiken
 * Hintergrundgrafiken werden initialisiert, positioniert und der Scene hinzugefügt.
 * Auch das Riesenrad in Level 1 wird hier initialisiert.
 * @param scene     : levelScene
 * @param level     : aktuelles Level
 * @author Flo
 */
RenderBackground::RenderBackground(QGraphicsScene *scene, int level) {
    //Hintergrundgrafiken werden initialisiert
    this->backgroundOne.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_1.png"));
    this->backgroundTwo.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_2.png"));
    this->backgroundThree.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_3.png"));
    this->backgroundFour.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_4.png"));

    //Das jeweils zweite Hintergrundbild wird positioniert
    this->backgroundTwo.setPos(imageLength,0);
    this->backgroundFour.setPos(imageLength,0);

    if(level == 1) {
        this->giantWheel[0].setPixmap(QPixmap(":/images/images/giantwheel_base.png"));
        this->giantWheel[0].setPos(800,335);

        this->giantWheel[1].setPixmap(QPixmap(":/images/images/giantwheel.png"));
        this->giantWheel[1].setParentItem(&giantWheel[0]);
        this->giantWheel[1].setPos(-81,-225);
        this->giantWheel[1].setTransformOriginPoint(251,251);

        for(int i=0;i<12;i++) {
            double param = (30*i*PI)/180;
            this->giantWheelBasket[i].setPixmap(QPixmap(":/images/images/giantwheel_basket.png"));
            this->giantWheelBasket[i].setParentItem(&giantWheel[1]);
            this->giantWheelBasket[i].setPos(sin(param)*243+234,cos(param)*243+245);
            this->giantWheelBasket[i].setTransformOriginPoint(17,3);

        }
    }

    //Grafiken werden der Scene hinzugefügt
    scene->addItem(&(this->backgroundOne));
    scene->addItem(&(this->backgroundTwo));
    if(level == 1) {
        scene->addItem(&(this->giantWheel[0]));
    }
    scene->addItem(&(this->backgroundThree));
    scene->addItem(&(this->backgroundFour));
}

/**
 * @brief Destruktor
 */
RenderBackground::~RenderBackground() {
}

/**
 * @brief verändern Position von Hintergrundgrafiken.
 * Funktion positioniert Hintergrundgrafiken neu.(nur "x" ändert sich, "y" ist immer 0)
 * @param x          : x-Position
 * @param background : Hintergrundgrafikitem
 */
void RenderBackground::setPos(int x, QGraphicsPixmapItem *background) {
    background->setPos(background->x() + x , background->y());
}

/**
 * @brief schiebt Hintergrundgrafiken vor den Spieler wenn dieser an ihnen vorbeigelaufen ist.
 * Immer wenn eine Hintergrundgrafik durch Spieler-Vorwärtsbewegung nicht mehr sichtbar ist wird sie
 * wieder nach vorne, vor den Spieler versetzt. So ist ein ständig sichtbarer Hintergrund gewährleistet.
 * @param x     : x-Position des linken Bildrandes im Level
 * @param level : aktuelles Level
 */
void RenderBackground::updateBackgroundPos(int x, int level) {
    if(x >= this->backgroundOne.x() + imageLength) {
        this->setPos(imageLength*2, &(this->backgroundOne));
    }
    if(x >= this->backgroundTwo.x() + imageLength) {
        this->setPos(imageLength*2, &(this->backgroundTwo));
    }
    if(x >= this->backgroundThree.x() + imageLength) {
        this->setPos(imageLength*2, &(this->backgroundThree));
    }
    if(x >= this->backgroundFour.x() + imageLength) {
        this->setPos(imageLength*2, &(this->backgroundFour));
    }
    if(level == 1) {
        if(x >= this->giantWheel[0].x() + imageLength) {
            this->setPos(imageLength*1.5, &(this->giantWheel[0]));
        }
    }
}

/**
 * @brief bewegt Parallaxe Ebenen mit einem bestimmten Anteil der Spielergeschwindigkeit.
 * Die Position der hinteren Hintergrundebene wird laufend so aktualisiert. Und zwar so dass sie sich mit
 * mit einem gewissen Teil der Geschwindigkeit des Spielers bewegt und eine Parallaxeeffekt entsteht.
 * Hier wird auch das Riesenrad rotiert.
 * @param x         : x-Wert der Positionsänderung des Spielers im aktuellen Step
 * @param stepCount : aktueller step
 * @param level     : aktuelles level
 */
void RenderBackground::updateParallaxe(int x, int stepCount, int level) {
    this->setPos(x*0.8, &(this->backgroundOne));
    this->setPos(x*0.8, &(this->backgroundTwo));
    this->setPos(x*0.2, &(this->giantWheel[0]));

    if(level == 1) {
        this->giantWheel[1].setRotation(-(stepCount/2));
        for(int i=0;i<12;i++) {
            this->giantWheelBasket[i].setRotation(stepCount/2);
        }
    }
}
