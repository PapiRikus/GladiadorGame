//
// Created by aaronsolera on 22/04/17.
//

#include "Gladiator.h"

Gladiator::Gladiator(char* resource, int row, int column, int width, int height,Map *m)  : Entity(resource,row,column,width,height,m){}

void Gladiator::draw(){
    Entity::moving();
    Entity::draw();
}

