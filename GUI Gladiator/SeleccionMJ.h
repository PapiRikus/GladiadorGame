//
// Created by aaronsolera on 17/05/17.
//

#ifndef PRUEBAS_SELECCIONMJ_H
#define PRUEBAS_SELECCIONMJ_H


#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

class SeleccionMJ {
private:
    int x,y;
    ALLEGRO_BITMAP *bitmap;
    bool estado;
    int metodoJuego;
public:
    SeleccionMJ(char* resourse,int x_, int y_);
    void draw();
    void mousePresionado(int mouseX,int mouseY);
    ~SeleccionMJ();

    bool getEstado();

    int getMetodoJuego() const;


};




#endif //PRUEBAS_SELECCIONMJ_H
