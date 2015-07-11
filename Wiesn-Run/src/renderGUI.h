#ifndef RENDERGUI_H
#define RENDERGUI_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

/**
 * @brief Hintergrund-Klasse
 * Eine Instanz wird bei jedem Levelstart in der Funktion Game::startNewGame angelegt.
 * Die Klasse initialisiert alle Grafikelemente die mit der Anzeige von Spielerwerten zu tun hat
 * (Gesundheit, Alkoholpegel, Munitionsvorrat, Punkte). Außerdem werden hier auch die angezeigten
 * Werte im Spiel fortlaufend aktualisiert.
 * @author Flo
 */
class RenderGUI {

public:
    //Konstruktor und Destruktor
    RenderGUI(QGraphicsScene *scene);
    ~RenderGUI();

    //aktualisiert die Position aller Elemente
    void setPos(int x);

    //aktualisiert die angezeigten Werte
    void setValues(int health, int alcohol, int ammo, int score);

private:

    //PixmapItems der angezeigten Spielerwerte
    QGraphicsTextItem showHealth;
    QGraphicsRectItem showHealthBar[2];
    QGraphicsTextItem showScore;
    QGraphicsTextItem showAmmo;
    QGraphicsTextItem showAlcohol;
    QGraphicsRectItem showAlcoholBar[2];

};

#endif // RENDERGUI_H
