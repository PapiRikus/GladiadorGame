

#include <allegro5/allegro_primitives.h>
#include "gladiador.h"

gladiador::gladiador(char* resourse,int x_, int y_, int vida_, int resistenciaGolpes_, int resistenciaPatadas_, int otra_resistecia_, int danoGolpe_, int danoPatada_, int danoExtra_) {
    vida = vida_;
    resistenciaGolpes  = resistenciaGolpes_;
    resistenciaPatadas = resistenciaPatadas_;
    otra_resistecia    = otra_resistecia_;
    danoGolpe = danoGolpe_;
    danopatada = danoPatada_;
    danoExtra = danoExtra_;
    turno = false;
    bitmapPosX   = 0;
    bitmapPosY   = 0;
    estado = -1;
    bitmap = al_load_bitmap(resourse);
    x = x_;
    y = y_;
}

void gladiador::Golpear(gladiador *gladiador, int tipoGolpe) {
    if(turno&&(gladiador->getEstado()==-1)) {
        turno = false;
        if (tipoGolpe == 0) {
            this->estado = 0;
            this->bitmapPosY = 200;
            this->bitmapPosX = 0;
            this->retraso = 0;
            gladiador->reducirvida(0, this->danoGolpe);
        }
        if (tipoGolpe == 1) {
            this->estado = 1;
            this->bitmapPosY = 400;
            this->bitmapPosX = 0;
            this->retraso = 0;
            gladiador->reducirvida(1, this->danoExtra);
        }
        if (tipoGolpe == 2) {
            this->estado = 2;
            this->bitmapPosY = 600;
            this->bitmapPosX = 0;
            this->retraso = 0;
            gladiador->reducirvida(2, this->danopatada);
        }
    }
}

void gladiador::setgladiador( int vida_, int resistenciaGolpes_, int resistenciaPatadas_, int otra_resistecia_, int danoGolpe_, int danoPatada_, int danoExtra_){
    vida = vida_;
    vida_original=vida_;
    resistenciaGolpes   = resistenciaGolpes_;
    resistenciaPatadas = resistenciaPatadas_;
    otra_resistecia     = otra_resistecia_;
    danoGolpe           = danoGolpe_;
    danopatada          = danoPatada_;
    danoExtra           = danoExtra_;
    estado = -1;
    bitmapPosX   = 0;
    bitmapPosY   = 0;
}

void gladiador::reducirvida(int tipoGolpe_, int dano_) {
    turno = true;
    if(tipoGolpe_ == 0){
        this->resistenciaGolpes = resistenciaGolpes-dano_;
        if(resistenciaGolpes<0){
            resistenciaGolpes = 0;
        }
    }if(tipoGolpe_ == 1){
        this->otra_resistecia = this->otra_resistecia - dano_;
        if(otra_resistecia<0){
            otra_resistecia = 0;
        }
    }if(tipoGolpe_ == 2){
        this->resistenciaPatadas = this->resistenciaPatadas - dano_;
        if(resistenciaPatadas<0){
            resistenciaPatadas = 0;
        }
    }
    vida = vida-dano_;
}

void gladiador::moveAt(int x_, int y_) {
    x =x_;
    y =y_;
}

void gladiador::drawResistanceBar() {
    al_draw_filled_rectangle(x, y-150/10, x+(vida/vida_original)*(150), y, LIGHT_BLUE);
}

void gladiador::draw(){
    if(retraso > 25){
        if(bitmapPosX < 450){
            bitmapPosX =  bitmapPosX + 150;
        }else{
            bitmapPosY = 0;
            bitmapPosX = 0;
            estado = -1;
        }
        retraso = 0;
    }else{
        retraso = retraso+1;
    }
    al_draw_bitmap_region(bitmap,bitmapPosX,bitmapPosY,150,150,x,y,NULL);  /// documentacion
}

int gladiador::getVida() const {
    return vida;
}

int gladiador::getResistenciaTotal() const {
    return resistenciaTotal;
}

int gladiador::getResistenciaGolpes() const {
    return resistenciaGolpes;
}

int gladiador::getResistenciaPatadas() const {
    return resistenciaPatadas;
}

int gladiador::getOtra_resistecia() const {
    return otra_resistecia;
}

int gladiador::getEstado() const {
    return estado;
}

int gladiador::getDanoGolpe() const {
    return danoGolpe;
}

int gladiador::getDanopatada() const {
    return danopatada;
}

int gladiador::getDanoExtra() const {
    return danoExtra;
}

bool gladiador::getTurno() const {
    return turno;
}

void gladiador::setTurno(bool turno) {
    gladiador::turno = turno;
}
