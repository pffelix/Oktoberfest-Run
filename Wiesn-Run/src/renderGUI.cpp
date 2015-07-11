#include "renderGUI.h"
#include "definitions.h"

#include <QGraphicsScene>
#include <QFont>


RenderGUI::RenderGUI(QGraphicsScene *scene) {

    this->showHealth.setPos(30, 30);
    this->showHealth.setDefaultTextColor(Qt::red);
    this->showHealth.setFont(QFont("Times",25));
    this->showHealth.setPlainText(QString("Gesundheit: "));

    this->showHealthBar.setParentItem(&showHealth);
    this->showHealthBar.setBrush(Qt::red);

    this->showScore.setParentItem(&showHealth);
    this->showScore.setPos(650, 0);
    this->showScore.setDefaultTextColor(Qt::yellow);
    this->showScore.setFont(QFont("Times",35));

    this->showAlcohol.setParentItem(&showHealth);
    this->showAlcohol.setPos(0, 50);
    this->showAlcohol.setDefaultTextColor(Qt::darkBlue);
    this->showAlcohol.setFont(QFont("Times",25));
    this->showAlcohol.setPlainText(QString("Alkoholpegel: "));

    this->showAlcoholBar.setParentItem(&showHealth);
    this->showAlcoholBar.setBrush(Qt::darkBlue);

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
    this->showHealthBar.setRect(210,10,(static_cast<float>(health)/maxHealth)*250,35);
    this->showAlcoholBar.setRect(210,60,(static_cast<float>(alcohol)/maxAlcohol)*250,35);
    this->showAmmo.setPlainText(QString("Munition: " + QString::number(ammo)));
    this->showScore.setPlainText(QString("Score: " + QString::number(score)));
}
