#include "enemy.h"

Enemy::Enemy() {
}


int Enemy::getHealth() const {
    return health;
}

void Enemy::setHealth(int health) {
    this->health = health;
}


int Enemy::getInflictedDamage() {
    return inflictedDamage;
}

bool Enemy::getDeath() {
    return death;
}

void Enemy::setDeath(bool death) {
    this->death = death;
}

void update() {

}
