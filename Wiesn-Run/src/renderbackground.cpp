#include "renderbackground.h"

#include <QGraphicsScene>

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

    //Grafiken werden der Scene hinzugefügt
    scene->addItem(&(this->backgroundOne));
    scene->addItem(&(this->backgroundTwo));
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
    background->setPos(background->x() + x , 0);
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
    else if(x >= this->backgroundTwo.x() + imageLength) {
        this->setPos(imageLength*2, &(this->backgroundTwo));
    }
    else if(x >= this->backgroundThree.x() + imageLength) {
        this->setPos(imageLength*2, &(this->backgroundThree));
    }
    else if(x >= this->backgroundFour.x() + imageLength) {
        this->setPos(imageLength*2, &(this->backgroundFour));
    }
}

/**
 * @brief RenderBackground::updateParallaxe
 * Die Position der hinteren Hintergrundebene wird laufend so aktualisiert. Und zwar so dass sie sich mit
 * halber Geschwindigkeit des Spielers bewegt und eine Parallaxeeffekt entsteht.
 * @param x     : x-Wert der Positionsänderung des Spielers im aktuellen Step
 * @author Flo
 */
void RenderBackground::updateParallaxe(int x) {
    this->setPos(x/2, &(this->backgroundOne));
    this->setPos(x/2, &(this->backgroundTwo));
}
