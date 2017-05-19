//
// Created by aaronsolera on 23/04/17.
//

#include "Queen.h"

Queen::Queen(char* resourse, int row, int column, Map *m) {
    plane = m;
    bitmap = al_load_bitmap(resourse);
    x =m->getX()+(m->getTiledSize())*column+10;
    y =m->getY()+(m->getTiledSize())*row;
}

void Queen::moveAt(int row, int column) {
    x =plane->getX()+(plane->getTiledSize())*column+10;
    y =plane->getY()+(plane->getTiledSize())*row;
}

void Queen::draw() {
    al_draw_bitmap_region(bitmap,0,0,50,50,x,y,NULL);
}