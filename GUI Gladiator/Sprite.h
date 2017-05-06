//
// Created by aaronsolera on 26/04/17.
//

#ifndef PRUEBAS_SPRITE_H
#define PRUEBAS_SPRITE_H

#include <iostream>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include "List.h"

using namespace std;

class Sprite{
public:
    int x, y, width, height, row_frame, colum_frame, speed, current_animation;
    ALLEGRO_BITMAP *bitmap;
    char *resource;
    struct animation{
        string id;
        float row, start_column, end_column;
    };
    List<animation*> *animations=new List<animation*>();
    Sprite(char* resource, int x, int y, int width, int height, int speed);
    ~Sprite();
    void setX(int x);
    void setY(int y);
    void draw();
    void setBitmap(char* resource);
    void setAnimation(string id);
    void insertAnimation(string id, int row, int end_column);
};


#endif //PRUEBAS_SPRITE_H
