//
// Created by aaronsolera on 17/05/17.
//

#ifndef PRUEBAS_BOTONES_H
#define PRUEBAS_BOTONES_H

#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include "gladiador.h"
#include <iostream>

class Botones {
private:
    int bitmapPosX,bitmapPosY;
    int cantidadBotones;
    int metodoSelecto;
    gladiador *gladiador1, *gladiador2;
    int x,y;
    ALLEGRO_BITMAP *bitmap;
public:
    Botones(char* resourse,int x_, int y_,gladiador *gladiador1_, gladiador *gladiador2_);
    void draw(int mouseX, int mouseY);
    void presionMouse(int mouseX, int mouseY);
    ~Botones();

    void setCantidadBotones(int cantidadBotones);

    void setMetodoSelecto(int metodoSelecto);
};


#endif //PRUEBAS_BOTONES_H
