#include "renderGUI.h"
#include "definitions.h"

#include <QGraphicsScene>
#include <QFont>

/**
 * @brief Konstruktor für alle Spielerwert Anzeigen
 * Die Grafikelemente der Anzeigen werden initialisiert, eingestellt und der Scene hinzugefügt
 * @param scene     : levelScene
 * @author Flo
 */
RenderGUI::RenderGUI(QGraphicsScene *scene) {
    //TextItem der Gesundheitsanzeige wird initalisiert
    this->showHealth.setPos(30, 30);
    this->showHealth.setDefaultTextColor(Qt::red);
    this->showHealth.setFont(QFont("Times",25));
    this->showHealth.setPlainText(QString("Gesundheit: "));

    //Gesundheitsbalken wird initialisiert
    this->showHealthBar[0].setParentItem(&showHealth);
    this->showHealthBar[0].setBrush(Qt::red);
    this->showHealthBar[1].setParentItem(&showHealth);
    this->showHealthBar[1].setRect(207,7,BARLENGTH+6,BARHEIGHT+6);

    //TextItem der Gesundheitsanzeige wird initalisiert
    this->showScore.setParentItem(&showHealth);
    this->showScore.setPos(650, 0);
    this->showScore.setDefaultTextColor(Qt::yellow);
    this->showScore.setFont(QFont("Times",35));

    //TextItem der Alkoholanzeige wird initalisiert
    this->showAlcohol.setParentItem(&showHealth);
    this->showAlcohol.setPos(0, 50);
    this->showAlcohol.setDefaultTextColor(Qt::darkBlue);
    this->showAlcohol.setFont(QFont("Times",25));
    this->showAlcohol.setPlainText(QString("Alkoholpegel: "));

    //Alkoholbalken wird initialisiert
    this->showAlcoholBar[0].setParentItem(&showHealth);
    this->showAlcoholBar[0].setBrush(Qt::darkBlue);
    this->showAlcoholBar[1].setParentItem(&showHealth);
    this->showAlcoholBar[1].setRect(207,57,BARLENGTH+6,BARHEIGHT+6);

    //TextItem der Munitionssanzeige wird initalisiert
    this->showAmmo.setParentItem(&showHealth);
    this->showAmmo.setPos(0, 100);
    this->showAmmo.setDefaultTextColor(Qt::darkGreen);
    this->showAmmo.setFont(QFont("Times",25));

    //Alle Anzeigen werden der Scene hinzugefügt
    scene->addItem(&(this->showHealth));
}

RenderGUI::~RenderGUI() {

}

/**
 * @brief RenderGUI::setPos
 * sorgt für eine Positionsänderung identisch mit der des Spielers auf der X-Achse
 * (Anzeigen bleiben auf den Spieler zentriert)
 * @param x     : x-Wert der Positionsänderung des Spielers im aktuellen Step
 * @author Flo
 */
void RenderGUI::setPos(int x) {
    this->showHealth.setPos(this->showHealth.x()+x, this->showHealth.y());
}

/**
 * @brief RenderGUI::setValues
 * Aktualisierung aller angezeigten Wert, Gesundheits- und Pegelbalken sind immer auf die maximal
 * möglichen Werte normiert
 * @param health    : aktueller Gesundheitswert
 * @param alcohol   : altueller Alkoholpegelwert
 * @param ammo      : aktueller Munitionsstand
 * @param score     : aktueller Punktestad
 * @author Flo
 */
void RenderGUI::setValues(int health, int alcohol, int ammo, int score) {
    this->showHealthBar[0].setRect(210,10,(static_cast<float>(health)/maxHealth)*BARLENGTH,BARHEIGHT);
    this->showAlcoholBar[0].setRect(210,60,(static_cast<float>(alcohol)/maxAlcohol)*BARLENGTH,BARHEIGHT);
    this->showAmmo.setPlainText(QString("Munition: " + QString::number(ammo)));
    this->showScore.setPlainText(QString("Score: " + QString::number(score)));
}
