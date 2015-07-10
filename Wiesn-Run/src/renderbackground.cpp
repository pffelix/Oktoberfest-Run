#include "renderbackground.h"

#include <QGraphicsScene>


RenderBackground::RenderBackground(QGraphicsScene *scene, int level) {

    this->backgroundOne.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_1.png"));
    this->backgroundTwo.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_2.png"));
    this->backgroundThree.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_3.png"));
    this->backgroundFour.setPixmap(QPixmap(":/images/images/bg_lev"+ QString::number(level) + "_4.png"));

    this->backgroundTwo.setPos(imageLength,0);
    this->backgroundFour.setPos(imageLength,0);

    scene->addItem(&(this->backgroundOne));
    scene->addItem(&(this->backgroundTwo));
    scene->addItem(&(this->backgroundThree));
    scene->addItem(&(this->backgroundFour));

}

RenderBackground::~RenderBackground() {

}

void RenderBackground::setPos(int x, QGraphicsPixmapItem *background) {
    background->setPos(background->x() + x , 0);
}

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

void RenderBackground::updateParallaxe(int x) {
    this->setPos(x, &(this->backgroundOne));
    this->setPos(x, &(this->backgroundTwo));
}
