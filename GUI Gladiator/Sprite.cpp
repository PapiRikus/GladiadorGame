//
// Created by aaronsolera on 26/04/17.
//

#include "Sprite.h"

Sprite::Sprite(char* resourse, int x, int y, int width, int height, int speed){
    this->bitmap = al_load_bitmap(resourse);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = speed;
    insertAnimation("DEFAULT", 0, 1);
    setAnimation("DEFAULT");
}

void Sprite::draw(){
    al_draw_bitmap_region(bitmap,width*((int)animations->Get(current_animation)->start_column%(int)animations->Get(current_animation)->end_column),height*animations->Get(current_animation)->row,width,height,x,y,NULL);
    animations->Get(current_animation)->start_column+=0.1*speed;
}

void Sprite::insertAnimation(string id, int row, int end_column) {
    animation *a = new animation();
    a->id = id;
    a->row = row;
    a->start_column=0;
    a->end_column= end_column;
    animations->Insert(a);
}

void Sprite::setBitmap(char *resource) {
    bitmap = al_load_bitmap(resource);
}

void Sprite::setAnimation(string id) {
    for (int i = 0; i < animations->length(); ++i) {
        if(animations->Get(i)->id == id){
            current_animation = i;
        }
    }
}

void Sprite::setX(int x) { this->x=x; }
void Sprite::setY(int y) { this->y=y; }
Sprite::~Sprite() {}