//
// Created by richard on 10/05/17.
//

#include "IA.h"
IA::IA() {

}
void IA::calcularGolpe(gladiador *gladiador1, gladiador *gladiador2) {
    if((gladiador1->getTurno())&&(gladiador2->getEstado()==-1)) {
        int pie, mano, espada, total;
        int random = rand() % (100 - 1);


        if (gladiador1->getDanopatada() > gladiador2->getResistenciaPatadas()) {
            pie = gladiador2->getResistenciaPatadas();
        } else {
            pie = gladiador1->getDanopatada();
        }
        if (gladiador1->getDanoExtra() > gladiador2->getOtra_resistecia()) {
            espada = gladiador2->getOtra_resistecia();
        } else {
            espada = gladiador1->getDanoExtra();
        }
        if (gladiador1->getDanoGolpe() > gladiador2->getResistenciaGolpes()) {
            mano = gladiador2->getResistenciaGolpes();
        } else {
            mano = gladiador1->getDanoGolpe();
        }
        std::cout<<"mano: "<<mano<< "pie: "<<pie<<"espada: "<<espada<<"vida: "<<gladiador2->getVida()<<std::endl;
        total = mano + espada + pie;
        if (!total == 0) {
            pie = (pie * 100) / total;
            mano = (mano * 100) / total;
            espada = (espada * 100) / total;
            std::cout << pie << std::endl;
            if (random <= mano) {
                std::cout << "go hand";
                gladiador1->Golpear(gladiador2, 0);
            } else if (random <= (espada + mano)) {
                std::cout << "go sword";
                gladiador1->Golpear(gladiador2, 1);
            } else if (random <= (espada + mano + pie)) {
                std::cout << "go food";
                gladiador1->Golpear(gladiador2, 2);
            }
        }
    }
}