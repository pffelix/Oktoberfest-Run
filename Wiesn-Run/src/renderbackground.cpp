#include "renderbackground.h"

#include <QGraphicsScene>
#include <math.h>       /* sin */

#define PI 3.14159265

/**
 * @brief Konstruktor für alle Hintergrundgrafiken
 * Hintergrundgrafiken werden initialisiert, positioniert und der Scene hinzugefügt
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

   /* this->giantWheel[0].setPixmap(QPixmap(":/images/images/giantwheel_base.png"));
    this->giantWheel[0].setPos(800,426);

    this->giantWheel[1].setPixmap(QPixmap(":/images/images/giantwheel.png"));
    this->giantWheel[1].setParentItem(&giantWheel[0]);
    this->giantWheel[1].setPos(-15,-165);
    this->giantWheel[1].setTransformOriginPoint(186,186);

    for(int i=0;i<12;i++) {
        double param = (30*i*PI)/180;
        this->giantWheelBasket[i].setPixmap(QPixmap(":/images/images/giantwheel_basket.png"));
        this->giantWheelBasket[i].setParentItem(&giantWheel[1]);
        this->giantWheelBasket[i].setPos(sin(param)*178+169,cos(param)*178+182);
        this->giantWheelBasket[i].setTransformOriginPoint(17,3);

    }*/

    //Grafiken werden der Scene hinzugefügt
    scene->addItem(&(this->backgroundOne));
    scene->addItem(&(this->backgroundTwo));
    //scene->addItem(&(this->giantWheel[0]));
    scene->addItem(&(this->backgroundThree));
    scene->addItem(&(this->backgroundFour));
}

RenderBackground::~RenderBackground() {

}

/**
 * @brief RenderBackground::setPos
 * Funktion positioniert Hintergrundgrafiken neu.(nur "x" ändert sich, "y" ist immer 0)
 * @param x          : x-Position
 * @param background : Hintergrundgrafikitem
 * @author Flo
 */
void RenderBackground::setPos(int x, QGraphicsPixmapItem *background) {
    background->setPos(background->x() + x , background->y());
}

/**
 * @brief RenderBackground::updateBackgroundPos
 * Immer wenn eine Hintergrundgrafik durch Spieler-Vorwärtsbewegung nicht mehr sichtbar ist wird sie
 * wieder nach vorne, vor den Spieler versetzt. So ist ein ständig sichtbarer Hintergrund gewährleistet.
 * @param x     : x-Position des linken Bildrandes im Level
 * @author Flo
 */
void RenderBackground::updateBackgroundPos(int x) {
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
    /*if(x >= this->giantWheel[0].x() + imageLength) {
        this->setPos(imageLength*2, &(this->giantWheel[0]));
    }*/
}

/**
 * @brief RenderBackground::updateParallaxe
 * Die Position der hinteren Hintergrundebene wird laufend so aktualisiert. Und zwar so dass sie sich mit
 * halber Geschwindigkeit des Spielers bewegt und eine Parallaxeeffekt entsteht.
 * @param x     : x-Wert der Positionsänderung des Spielers im aktuellen Step
 * @author Flo
 */
void RenderBackground::updateParallaxe(int x, int stepCount) {
    this->setPos(x*0.8, &(this->backgroundOne));
    this->setPos(x*0.8, &(this->backgroundTwo));
    //this->setPos(x*0.2, &(this->giantWheel[0]));

    /*this->giantWheel[1].setRotation(-(stepCount/2));
    for(int i=0;i<12;i++) {
        this->giantWheelBasket[i].setRotation(stepCount/2);
    }*/
}
