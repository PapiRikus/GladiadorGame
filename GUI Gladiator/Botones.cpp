//
// Created by richard on 09/05/17.
//

#include "Botones.h"
Botones::Botones(char* resourse,int x_, int y_,gladiador *gladiador1_, gladiador *gladiador2_) {
    gladiador1 = gladiador1_;
    gladiador2 = gladiador2_;
    x = x_;
    y = y_;
    bitmap = al_load_bitmap(resourse);
}

void Botones::draw(int mouseX, int mouseY) {
    if((gladiador1->getEstado()==-1)&&(gladiador2->getEstado()==-1)) {
        for (int i = 0; i < 6; ++i) {
            if ((i < 3) && (gladiador1->getTurno())) {
                if ((x + 100 + (100 * i) >= mouseX) && (mouseX >= x + (100 * i)) && (mouseY >= y) &&
                    (mouseY <= y + 100)) {
                    al_draw_bitmap_region(bitmap, 100 * i, 100, 100, 100, x + (100 * i), y, NULL);
                } else {
                    al_draw_bitmap_region(bitmap, 100 * i, 0, 100, 100, x + (100 * i), y, NULL);
                }

            }else if((gladiador2->getTurno()&&(i>=3))){
                if ((x + 100 + (100 * i) >= mouseX) && (mouseX >= x + (100 * i)) && (mouseY >= y) &&
                    (mouseY <= y + 100)) {
                    al_draw_bitmap_region(bitmap, 100 * i, 100, 100, 100, x + (100 * i), y, NULL);
                } else {
                    al_draw_bitmap_region(bitmap, 100 * i, 0, 100, 100, x + (100 * i), y, NULL);
                }
            }
        }
    }
}

void Botones::presionMouse(int mouseX, int mouseY) {
    for (int i = 0; i < 6; ++i) {
        if((gladiador1->getEstado()==-1)&&(gladiador2->getEstado()==-1)) {
            if ((x + 100 + (100 * i) >= mouseX) && (mouseX >= x + (100 * i)) && (mouseY >= y) && (mouseY <= y + 100)) {
                std::cout << "dentro del rango";
                std::cout << "    pos i " << i << std::endl;
                if ((i >= 3) && (gladiador2->getTurno())) {
                    gladiador2->Golpear(gladiador1, i % 3);
                } else if((i<3)&&(gladiador1->getTurno())) {
                    gladiador1->Golpear(gladiador2, i);
                }
            }
        }
    }
}

Botones::~Botones() {

}

void Botones::setCantidadBotones(int cantidadBotones) {
    Botones::cantidadBotones = cantidadBotones;
}

void Botones::setMetodoSelecto(int metodoSelecto) {
    Botones::metodoSelecto = metodoSelecto;
}
