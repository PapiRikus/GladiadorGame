//
// Created by aaronsolera on 28/04/17.
//

#include "Tiled.h"

Tiled::Tiled(char* resource, int x, int y, int size, int isSolid) {
    this->resource=resource;
    this->x=x;
    this->y=y;
    this->size=size;
    this->isSolid=isSolid;
    sprite = new  Sprite(resource, x, y, size, size, 0);
}
char* Tiled::getResource() { return resource; }
int Tiled::getX() { return x; }
int Tiled::getY() { return y; }
int Tiled::getSize() { return size; }
void Tiled::draw() { sprite->draw(); }
int Tiled::getIsSolid() { return isSolid; }

Tiled::~Tiled() {}