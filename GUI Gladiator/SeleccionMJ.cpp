//
// Created by richard on 09/05/17.
//

#include "SeleccionMJ.h"
SeleccionMJ::SeleccionMJ(char *resourse, int x_, int y_) {
    estado = false;
    x = x_;
    y = y_;
    bitmap = al_load_bitmap(resourse);
}
void SeleccionMJ::draw() {
    for (int i = 0; i < 3; ++i) {
        al_draw_bitmap_region(bitmap, 200 * i, 100, 100, 55,x + (150 * i), y, NULL);
    }
}
void SeleccionMJ::mousePresionado(int mouseX, int mouseY) {
    for (int i = 0; i < 3; ++i) {
        if ((x + 100 + (150 * i) >= mouseX) && (mouseX >= x + (150 * i)) && (mouseY >= y) && (mouseY <= y + 50)) {
            metodoJuego = i;
            estado = true;
            al_draw_bitmap_region(bitmap, 200 * i, 100, 100, 55,x + (150 * i), y, NULL);
        }
    }
}
SeleccionMJ::~SeleccionMJ() {

}

bool SeleccionMJ::getEstado(){
    return estado;
}

int SeleccionMJ::getMetodoJuego() const {
    return metodoJuego;
}

