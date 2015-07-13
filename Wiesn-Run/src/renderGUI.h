#ifndef RENDERGUI_H
#define RENDERGUI_H
#define BARLENGTH (250)
#define BARHEIGHT (35)

#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

/**
 * @brief Anzeigen der Spielerwerte-Klasse
 * Eine Instanz wird bei jedem Levelstart in der Funktion Game::startNewGame angelegt.
 * Die Klasse initialisiert alle Grafikelemente die mit der Anzeige von Spielerwerten zu tun hat
 * (Gesundheit, Alkoholpegel, Munitionsvorrat, Punkte). Außerdem werden hier auch die angezeigten
 * Werte im Spiel fortlaufend aktualisiert.
 * Alle Elemente sind "Kinder" der Gesundheitsanzeige um Positionsaktualisierungen zu vereinfachen
 * (Kindelemente verhalten sich immer relativ um Elternobjekt und werden auch automatisch mit diesem
 * der Scene hinzugefügt bzw. auch wieder entfernt)
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
    void setValues(int health, int alcohol, int ammo, int score, int stepCount);

private:

    //PixmapItems der angezeigten Spielerwerte
    QGraphicsPixmapItem showHealth;
    QGraphicsRectItem showHealthBar[2];
    QGraphicsPixmapItem showScore;
    QGraphicsTextItem showScoreValue;
    QGraphicsPixmapItem showAmmo;
    QGraphicsTextItem showAmmoValue;
    QGraphicsPixmapItem showAlcohol;
    QGraphicsRectItem showAlcoholBar[2];

};

#endif // RENDERGUI_H
