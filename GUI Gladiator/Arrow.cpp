//
// Created by aaronsolera on 07/05/17.
//

#include "Arrow.h"

Arrow::Arrow(char *bitmap, int row, int column, int width, int height, Map *m) : Entity(bitmap, row, column, width, height, m){ setSpeed(50); }

void Arrow::draw() {
    Entity::draw();
    Entity::moving();
}
void Arrow::setDamage(float damage) { this->damage = damage; }
int Arrow::getDamage() { return damage; }