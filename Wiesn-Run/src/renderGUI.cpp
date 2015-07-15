#include "renderGUI.h"
#include "definitions.h"

#include <QGraphicsScene>
#include <QFont>

/**
 * @brief Konstruktor für alle Spielerwert Anzeigen
 * Die Grafikelemente der Anzeigen werden initialisiert, eingestellt und der Scene hinzugefügt
 * Alle Elemente bekommen die Gesundheitsanzeige als Elternobjekt zugewiesen.
 * @param scene     : levelScene
 */
RenderGUI::RenderGUI(QGraphicsScene *scene) {
    //TextItem der Gesundheitsanzeige wird initalisiert
    this->showHealth.setPos(20, 15);
    this->showHealth.setPixmap(QPixmap(":/images/images/heart.png"));

    //Gesundheitsbalken wird initialisiert
    this->showHealthBar[0].setParentItem(&showHealth);
    this->showHealthBar[0].setBrush(Qt::red);
    this->showHealthBar[1].setParentItem(&showHealth);
    this->showHealthBar[1].setRect(137,12,BARLENGTH+6,BARHEIGHT+6);

    //TextItem der Scoreanzeige wird initalisiert
    this->showScoreValue.setParentItem(&showHealth);
    this->showScoreValue.setPos(760, -15);
    this->showScoreValue.setDefaultTextColor(Qt::black);
    this->showScoreValue.setFont(QFont("Times",50));

    //
    this->showScore.setParentItem(&showHealth);
    this->showScore.setPixmap(QPixmap(":/images/images/score.png"));
    this->showScore.setPos(550, 0);

    //TextItem der Alkoholanzeige wird initalisiert
    this->showAlcohol.setParentItem(&showHealth);
    this->showAlcohol.setPixmap(QPixmap(":/images/images/pegel.png"));
    this->showAlcohol.setPos(0, 75);

    //Alkoholbalken wird initialisiert
    this->showAlcoholBar[0].setParentItem(&showHealth);
    this->showAlcoholBar[0].setBrush(Qt::darkBlue);
    this->showAlcoholBar[1].setParentItem(&showHealth);
    this->showAlcoholBar[1].setRect(137,87,BARLENGTH+6,BARHEIGHT+6);

    //TextItem der Munitionssanzeige wird initalisiert
    this->showAmmoValue.setParentItem(&showHealth);
    this->showAmmoValue.setPos(760, 60);
    this->showAmmoValue.setDefaultTextColor(Qt::darkGreen);
    this->showAmmoValue.setFont(QFont("Times",50));

    this->showAmmo.setParentItem(&showHealth);
    this->showAmmo.setPixmap(QPixmap(":/images/images/ammo.png"));
    this->showAmmo.setPos(600, 75);

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
 */
void RenderGUI::setPos(int x) {
    this->showHealth.setPos(this->showHealth.x()+x, this->showHealth.y());
}

/**
 * @brief RenderGUI::setValues
 * Aktualisierung aller angezeigten Wert, Gesundheits- und Pegelbalken sind immer auf die maximal
 * möglichen Werte normiert. Wird der maximale Alkoholwert überschritten blinkt der Balken Rot
 * da der Spieler Schaden bekommt.
 * @param health    : aktueller Gesundheitswert
 * @param alcohol   : altueller Alkoholpegelwert
 * @param ammo      : aktueller Munitionsstand
 * @param score     : aktueller Punktestad
 * @param stepCount : aktueller Step
 */
void RenderGUI::setValues(int health, int alcohol, int ammo, int score, int stepCount) {
    this->showHealthBar[0].setRect(140,15,(static_cast<float>(health)/maxHealth)*BARLENGTH,BARHEIGHT);
    this->showAmmoValue.setPlainText(QString(QString::number(ammo)));
    this->showScoreValue.setPlainText(QString(QString::number(score)));

    //AlkoholMax überschritten?
    if(alcohol>maxAlcohol) {
        this->showAlcoholBar[0].setRect(140,90,BARLENGTH,BARHEIGHT);

        //Balken blinkt rot auf
        if(stepCount%(frameRate*2) == 0) {
            this->showAlcoholBar[0].setBrush(Qt::darkBlue);
        }
        else if(stepCount%frameRate == 0) {
            this->showAlcoholBar[0].setBrush(Qt::red);
        }
    }
    else {
        this->showAlcoholBar[0].setBrush(Qt::darkBlue);
        this->showAlcoholBar[0].setRect(140,90,(static_cast<float>(alcohol)/maxAlcohol)*BARLENGTH,BARHEIGHT);
    }
}
