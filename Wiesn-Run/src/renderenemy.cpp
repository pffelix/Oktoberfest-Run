#include "renderenemy.h"

RenderEnemy::RenderEnemy() {
}

RenderEnemy::~RenderEnemy() {
}

void RenderEnemy::render(int x) {
    this->posX = x * (1024/300);
    setPixmap(QPixmap(":/images/images/enemy.png"));
    setPos(posX,(450));
}
