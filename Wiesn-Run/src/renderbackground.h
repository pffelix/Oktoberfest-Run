#ifndef RENDERBACKGROUND_H
#define RENDERBACKGROUND_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

/**
 * @brief Hintergrund-Klasse
 * Eine Instanz wird bei jedem Levelstart in der Funktion Game::startNewGame angelegt.
 * Die Klasse initialisiert alle Hintergrundgrafiken und aktualisiert deren Positionen im
 * laufendem Spiel. Auch die Bewegungsparallaxe wird hier berechnet.
 * Jede Hintergrundebene besteht immer aus zwei nebeneinander stehenden Bildern.
 * Ist eines davon, bedingt durch die Vorwärtsbewegung des Spielers nicht mehr sichtbar, so wird es wieder
 * am zweiten Bild vorbei, nach vorne geschoben. So wird gewährleistet das der Spieler nicht
 * an den Bildern "vorbeiläuft".
 * @author Flo
 */
class RenderBackground {

public:
    //Konstruktor und Destruktor
    RenderBackground(QGraphicsScene *scene, int level);
    ~RenderBackground();

    //aktualisiert die Position der entsprechenden Hintergrundgrafik
    void setPos(int x, QGraphicsPixmapItem *background);

    //berechnet die Bewegung der Hintergrund Bewegungsparallaxe
    void updateParallaxe(int x, int stepCount, int level);

    //schiebt Hintergrundgrafiken wieder vor den Spieler wenn dieser an ihnen vorbeigelaufen ist
    void updateBackgroundPos(int x, int level);

private:

    //PixmapItems der Hintergrundgrafiken
    QGraphicsPixmapItem backgroundOne;
    QGraphicsPixmapItem backgroundTwo;
    QGraphicsPixmapItem backgroundThree;
    QGraphicsPixmapItem backgroundFour;

    QGraphicsPixmapItem giantWheel[3];
    QGraphicsPixmapItem giantWheelBasket[12];

    //Bildbreite der Hintergrundgrafiken
    int imageLength = 2560;
};

#endif // RENDERBACKGROUND_H
