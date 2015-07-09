#include "renderGUI.h"
#include "definitions.h"
#include <QFont>
#include <QGraphicsScene>
#include "game.h"

extern Game * game;

RenderGUI::RenderGUI() {

    this->showScore.setPlainText(QString("Score: "));
    this->showScore.setPos(670, 300);
    this->showScore.setDefaultTextColor(Qt::yellow);
    this->showScore.setFont(QFont("Times",35));

}

RenderGUI::~RenderGUI() {

}

