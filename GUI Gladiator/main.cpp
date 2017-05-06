#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Gladiator.h"
#include "Tower.h"

//Constantes definidas (Colores, dimensiones, medidas, entre otros)
#define screen_width 800
#define screen_height 600
#define SAND al_map_rgb(225, 204, 79)
#define WHITE al_map_rgb(255, 255, 255)
#define FPS 60.0

using namespace std;

int moveX=0, moveY=0;//Variables paramover el jugador
bool run=true;//Booleano que ejecuta el loop
bool pressed = false;

ALLEGRO_DISPLAY *display;//Variable global ventana, se utiliza para mostrar el juego
ALLEGRO_EVENT_QUEUE *event_queue;//Variable de la cola de eventos
ALLEGRO_FONT *font;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT events;
ALLEGRO_BITMAP *player_sprite;
ALLEGRO_KEYBOARD_STATE keyState;
Map *zone1, *zone2;
Gladiator *gladiator1;
Tower *tower1;
//Inicialización de todos los componentas para el juego, aquí deben definirse las variables
void initialize(){
    al_init();//Inicia componentes básicos para usar alegro
    al_init_font_addon();//Inicializa los formato de letra
    al_init_ttf_addon();//Inicializa los archivos de tipos de letras
    al_init_primitives_addon();//Inicializa formas primitivas(rectángulos, triángulos, círculos, entre otros)
    al_install_keyboard();//Inicializa el teclado
    al_init_image_addon();//Inicializa imagenes

    font = al_load_font("game_font.ttf", 12, NULL);//Establece el formato de letra
    display = al_create_display(screen_width, screen_height);//Crea ventana con dimensiones
    timer = al_create_timer(1.0/FPS);//Temporizador de frames del loop
    event_queue = al_create_event_queue();//Cola de eventos (del teclado, mouse, display, etc)
    player_sprite = al_load_bitmap("gladiator.png");//Establece una imagen al bitmap

    al_register_event_source(event_queue,al_get_keyboard_event_source());//Registra los eventos de teclado en la cola
    al_register_event_source(event_queue,al_get_display_event_source(display));//Registrando eventos display en la cola
    al_register_event_source(event_queue,al_get_timer_event_source(timer));//Registra evento del temporizador en la cola
    al_start_timer(timer);//Inicia el temporizador del loop

    zone1 = new Map(50,50,5,10,50);
    zone2 = new Map(50,300,5,10,50);
    zone2->addBitmap("dirt.png");
    zone1->addBitmap("white_cell.png");
    zone1->addBitmap("dirt.png");
    char* map="0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,";
    zone1->setBackground(map,',','/');
    zone2->setBackground(map,',','/');
    gladiator1 = new Gladiator("gladiator.png", zone1->getRows()/2, 0, 40, 40, zone1);
    tower1 = new Tower("tower.png", 2, 4, 50, 70, zone1);
}

//Manejador de eventos. Aquí se establecen y administran eventos de teclado, mouse, display, entre otros.
void eventsHandler(){
    //Evento que finaliza el loop al cerrar la ventana
    if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        run = false;
    }
}

//Loop que dibuja y actualiza los componentes del juego
void loop(){
        if(events.type==ALLEGRO_EVENT_TIMER){
            if(al_key_down(&keyState, ALLEGRO_KEY_UP)){
                if(!pressed){
                    gladiator1->moveAt(gladiator1->getEndPathRow() - 1, gladiator1->getEndPathColumn());
                    pressed = true;
                }
            } else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
                if(!pressed) {
                    gladiator1->moveAt(gladiator1->getEndPathRow() + 1, gladiator1->getEndPathColumn());
                    pressed = true;
                }
            } else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
                if(!pressed) {
                    gladiator1->moveAt(gladiator1->getEndPathRow(), gladiator1->getEndPathColumn() - 1);
                    pressed = true;
                }
            } else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
                if(!pressed){
                    gladiator1->moveAt(gladiator1->getEndPathRow(), gladiator1->getEndPathColumn() + 1);
                    pressed = true;
                }
            } else {
                pressed=false;
            }
            zone1->draw();
            zone2->draw();
            gladiator1->draw();
            tower1->draw();
            al_draw_text(font, WHITE, screen_width/2,0, ALLEGRO_ALIGN_CENTER,"genetic gladiator");//Muestra texto en pantalla
            al_flip_display();//Refresca pantalla
            al_clear_to_color(SAND);//Repinta fondo
        }
}

int main() {
    initialize();

    while(run) {
        al_wait_for_event(event_queue, &events);
        al_get_keyboard_state(&keyState);
        eventsHandler();
        loop();
    }

    al_destroy_bitmap(player_sprite);//Libera memoria de los bitmaps
    al_destroy_display(display);//Liberar del display
    al_destroy_font(font);//Libera memoria de la letra

    return 0;
}