#ifndef RENDERENEMY_H
#define RENDERENEMY_H

class RenderEnemy {
public:

    //Konstruktor und Destruktor
    RenderEnemy();
    ~RenderEnemy();

private:
    //Attribute Grafikelement "Enemy"
    struct postion;
    bool attacks;
    bool isDead;
    bool getsDamage;
    bool runs;
    int enemyType;

};

#endif // RENDERENEMY_H
