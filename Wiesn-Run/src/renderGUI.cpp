#include "renderGUI.h"
#include <QFont>


RenderGUI::RenderGUI() {

    this->showHealth.setPos(30, 30);
    this->showHealth.setDefaultTextColor(Qt::red);
    this->showHealth.setFont(QFont("Times",25));

    this->showScore.setParentItem(&showHealth);
    this->showScore.setPos(650, 0);
    this->showScore.setDefaultTextColor(Qt::yellow);
    this->showScore.setFont(QFont("Times",35));

    this->showAlcohol.setParentItem(&showHealth);
    this->showAlcohol.setPos(0, 50);
    this->showAlcohol.setDefaultTextColor(Qt::black);
    this->showAlcohol.setFont(QFont("Times",25));

    this->showAmmo.setParentItem(&showHealth);
    this->showAmmo.setPos(0, 100);
    this->showAmmo.setDefaultTextColor(Qt::darkGreen);
    this->showAmmo.setFont(QFont("Times",25));

}

RenderGUI::~RenderGUI() {

}

void RenderGUI::setPos(int x) {
    this->showHealth.setPos(this->showHealth.x()+x, this->showHealth.y());
}

void RenderGUI::setValues(int health, int ammo, int alcohol, int score) {
    this->showHealth.setPlainText(QString("Gesundheit: " + QString::number(health)));
    this->showAmmo.setPlainText(QString("Alkoholpegel: " + QString::number(ammo)));
    this->showAlcohol.setPlainText(QString("Munition: " + QString::number(alcohol)));
    this->showScore.setPlainText(QString("Score: " + QString::number(score)));
}
