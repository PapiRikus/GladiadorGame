//
// Created by richard on 26/04/17.
//

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Matrix.h"
#include "Gladiator.h"
#include "Queen.h"
#include <pthread.h>
//Constantes definidas (Colores, dimensiones, medidas, entre otros)
#define screen_width 500
#define screen_height 500
#define BLACK al_map_rgb(0,0,0)
#define WHITE al_map_rgb(255, 255, 255)
#define LIGTH_BLUE al_map_rgb(44, 117, 255)
#define GREY al_map_rgb(150,150,150)
#define FPS 60.0

#include "backtracking.h"
#ifndef PRUEBAS_VENTANAALE_H
#define PRUEBAS_VENTANAALE_H


class VentanaAle {
public:
    void addQueen(int row, int column);
    void move_queens(int q[]);
    int moveX=0, moveY=0;//Variables paramover el jugador
    bool run=true;//Booleano que ejecuta el loop
    backtracking *backtrack;
    ALLEGRO_DISPLAY *display;//Variable global ventana, se utiliza para mostrar el juego
    ALLEGRO_EVENT_QUEUE *event_queue;//Variable de la cola de eventos
    ALLEGRO_FONT *font;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT events;
    ALLEGRO_KEYBOARD_STATE keyState;
    Map *zone1;
    List<Queen*> *queens;
    VentanaAle();
    ~VentanaAle();
    void eventsHandler();
    void* loop();
};


#endif //PRUEBAS_VENTANAALE_H
