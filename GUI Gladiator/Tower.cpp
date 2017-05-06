//
// Created by aaronsolera on 28/04/17.
//

#include "Tower.h"

Tower::Tower(char *resource, int row, int column, int width, int height, Map *m) : Entity(resource,row,column,width,height,m) { plane->setSolidTiledAt(row, column, 1); }