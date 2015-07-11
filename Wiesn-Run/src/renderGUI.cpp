#include "renderGUI.h"
#include "definitions.h"

#include <QGraphicsScene>
#include <QFont>


RenderGUI::RenderGUI(QGraphicsScene *scene) {

    this->showHealth.setPos(30, 30);
    this->showHealth.setDefaultTextColor(Qt::red);
    this->showHealth.setFont(QFont("Times",25));
    this->showHealth.setPlainText(QString("Gesundheit: "));

    this->showHealthBar[0].setParentItem(&showHealth);
    this->showHealthBar[0].setBrush(Qt::red);
    this->showHealthBar[1].setParentItem(&showHealth);
    this->showHealthBar[1].setRect(207,7,256,41);

    this->showScore.setParentItem(&showHealth);
    this->showScore.setPos(650, 0);
    this->showScore.setDefaultTextColor(Qt::yellow);
    this->showScore.setFont(QFont("Times",35));

    this->showAlcohol.setParentItem(&showHealth);
    this->showAlcohol.setPos(0, 50);
    this->showAlcohol.setDefaultTextColor(Qt::darkBlue);
    this->showAlcohol.setFont(QFont("Times",25));
    this->showAlcohol.setPlainText(QString("Alkoholpegel: "));

    this->showAlcoholBar[0].setParentItem(&showHealth);
    this->showAlcoholBar[0].setBrush(Qt::darkBlue);
    this->showAlcoholBar[1].setParentItem(&showHealth);
    this->showAlcoholBar[1].setRect(207,57,256,41);

    this->showAmmo.setParentItem(&showHealth);
    this->showAmmo.setPos(0, 100);
    this->showAmmo.setDefaultTextColor(Qt::darkGreen);
    this->showAmmo.setFont(QFont("Times",25));

    scene->addItem(&(this->showHealth));
}

RenderGUI::~RenderGUI() {

}

void RenderGUI::setPos(int x) {
    this->showHealth.setPos(this->showHealth.x()+x, this->showHealth.y());
}

void RenderGUI::setValues(int health, int alcohol, int ammo, int score) {
    this->showHealthBar[0].setRect(210,10,(static_cast<float>(health)/maxHealth)*250,35);
    this->showAlcoholBar[0].setRect(210,60,(static_cast<float>(alcohol)/maxAlcohol)*250,35);
    this->showAmmo.setPlainText(QString("Munition: " + QString::number(ammo)));
    this->showScore.setPlainText(QString("Score: " + QString::number(score)));
}
