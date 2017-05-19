//
// Created by aaronsolera on 17/05/17.
//

#ifndef PRUEBAS_GLADIADOR_H
#define PRUEBAS_GLADIADOR_H
#define LIGHT_BLUE al_map_rgb(51, 153, 255)
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

class gladiador {
private:
    ALLEGRO_BITMAP *bitmap;
    int vida, vida_original;
    bool turno;
    int metodoJuegoSeleccionado;
    int estado;//esta variable almacena el estado del gladiador el cual puede estar atacando o no
    int resistenciaTotal; // resistencia total del gladiador
    int resistenciaGolpes; //resistencia a los golpes recibidos
    int resistenciaPatadas; //resistencia a patadas recibidas
    int otra_resistecia;
    int danoGolpe;
    int danopatada;
    int danoExtra;
    int bitmapPosX,bitmapPosY;
    int x,y;
    int retraso = 0;
    void drawResistanceBar();
public:
    int getVida() const;

    int getResistenciaTotal() const;

    int getResistenciaGolpes() const;

    int getResistenciaPatadas() const;

    int getOtra_resistecia() const;

    gladiador(char* bitmap,int x_, int y_, int vida_, int resistenciaGolpes_, int resistenciaPatadas_,
              int otra_resistecia_, int danoGolpe_, int danoPatada_, int danoExtra_);
    void Golpear(gladiador *gladiador, int tipoGolpe);
    void reducirvida(int tipoGolpe_,int dano_);
    void moveAt(int row, int collumn);
    ~gladiador();
    void draw();

    int getEstado() const;

    bool getTurno() const;

    void setTurno(bool turno);

    void setMetodoJuegoSeleccionado(int metodoJuegoSeleccionado);

    int getDanoGolpe() const;

    int getDanopatada() const;

    int getDanoExtra() const;
    void setgladiador( int vida_, int resistenciaGolpes_, int resistenciaPatadas_, int otra_resistecia_, int danoGolpe_, int danoPatada_, int danoExtra_);
};



#endif //PRUEBAS_GLADIADOR_H
