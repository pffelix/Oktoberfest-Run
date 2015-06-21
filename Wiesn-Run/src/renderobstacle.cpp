#include "renderobstacle.h"

RenderObstacle::RenderObstacle() {
}

RenderObstacle::~RenderObstacle() {
}

void RenderObstacle::render(int x) {
    this->posX = x * (1024/300);
    setPixmap(QPixmap(":/images/images/obstacle.png"));
    setPos(posX,(450));
}
