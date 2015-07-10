#include "renderbackground.h"

#include <QGraphicsScene>

RenderBackground::RenderBackground(QGraphicsScene *scene) {

    this->backgroundOne.setPixmap(QPixmap(":/images/images/bg_lev1_1.png"));
    this->backgroundTwo.setPixmap(QPixmap(":/images/images/bg_lev1_2.png"));
    this->backgroundThree.setPixmap(QPixmap(":/images/images/bg_lev1_3.png"));
    this->backgroundFour.setPixmap(QPixmap(":/images/images/bg_lev1_4.png"));

    this->backgroundTwo.setPos(2560,0);
    this->backgroundFour.setPos(2560,0);

    scene->addItem(&(this->backgroundOne));
    scene->addItem(&(this->backgroundTwo));
    scene->addItem(&(this->backgroundThree));
    scene->addItem(&(this->backgroundFour));

}

RenderBackground::~RenderBackground() {

}

