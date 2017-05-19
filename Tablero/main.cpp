#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Matrix.h"

#include "Gladiator.h"
#include "Queen.h"


//Constantes definidas (Colores, dimensiones, medidas, entre otros)
#define screen_width 500
#define screen_height 500
#define BLACK al_map_rgb(0,0,0)
#define WHITE al_map_rgb(255, 255, 255)
#define LIGTH_BLUE al_map_rgb(44, 117, 255)
#define GREY al_map_rgb(150,150,150)
#define FPS 60.0

#include "VentanaAle.h"
bool inicializar = true;
#include "backtracking.h"
#include <fstream>

using namespace std;

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

void addQueen(int row, int column){
    queens->Insert(new Queen("queen.png",row,column,zone1));
}
void move_queens(int q[]){
    for (int i = 0; i < sizeof(q); ++i) {
        queens->Get(i)->moveAt(q[i],i);
    }
}
//Inicialización de todos los componentas para el juego, aquí deben definirse las variables
void initialize(){
   backtrack = new backtracking();


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

    al_register_event_source(event_queue,al_get_keyboard_event_source());//Registra los eventos de teclado en la cola
    al_register_event_source(event_queue,al_get_display_event_source(display));//Registrando eventos display en la cola
    al_register_event_source(event_queue,al_get_timer_event_source(timer));//Registra evento del temporizador en la cola
    al_start_timer(timer);//Inicia el temporizador del loop
    zone1 = new Map(50,50,8,8,50);
    zone1->addBitmap("white_cell.png");
    zone1->addBitmap("black_cell.png");
    char* map="1,0,1,0,1,0,1,0,-0,1,0,1,0,1,0,1,-1,0,1,0,1,0,1,0,-0,1,0,1,0,1,0,1,-1,0,1,0,1,0,1,0,-0,1,0,1,0,1,0,1,-1,0,1,0,1,0,1,0,-0,1,0,1,0,1,0,1,";
    zone1->setBackground(map,',','-');
    queens= new List<Queen*>();
    for (int i = 0; i < 8; ++i){
        addQueen(i,-1);
    }

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
                moveY--;
            } else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
                moveY++;
            } else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
                moveX--;
            } else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
                moveX++;
            }
            zone1->draw();                  //dibuja el tablero
            for (int i = 0; i < queens->length(); ++i) {    // dibuja las reinas
                queens->Get(i)->draw();                     //dibuja cada una de las reinas por invididual
            }

            al_draw_text(font, WHITE, screen_width/2, 0, ALLEGRO_ALIGN_CENTER,"soluciones de las 8 reinas: ");//Muestra texto en pantalla
            al_flip_display();//Refresca pantalla
            al_clear_to_color(GREY);//Repinta fondo
        }
}



int main() {
    initialize();


      FILE *file;
        FILE *pf;
    pf = fopen("texto.txt","w");
    // fclose(pf);
    fstream salida;
     salida.open("texto.txt",ios::out);
     if(salida.is_open()){
         cout<<"me abro";
         salida<<"1jdkajlskdjfka"<<endl;
         salida<<"salida 2"<<endl;
     }

     salida.close();
      //fclose(file);
      int location[8] = {-1,-1,-1,-1,-1,-1,-1,-1};

    backtrack->bactrack8Queens(location,0,0);

    FILE *miArchivo;
    miArchivo = fopen("texto.txt","r");
    char punto;


   // ifstream fe("texto.txt",ios::in| ios::binary);

    //fe>>punto;
    //cout<<"imprimo el punto "<< punto;
   // pthread_create(&hilo,NULL,&pantalla,NULL);

    //esto es necesario

 /*   for(int arduino = 0;arduino < 8;arduino++) {

        if(location[arduino]==-1){
            fprintf(file, "%d",8); //Writing to the file
        }else{
            fprintf(file, "%d", location[arduino]); //Writing to the file
        }
    }*/
int contador = 0;
    while(run) {
        if((contador%500)==0) {                         //esta seccion lo que hace es realizar la actuilizacion de las reinas cada 500 actualizaciones
            file = fopen("/dev/ttyACM0", "w");          //conexion con el arduino
            for (int i = 0; i < 8; i++) {               //ciclo encargardo de leer las 8 reinas
                fscanf(miArchivo, "%s", &punto);        //escanea el archivo
                //cout << punto << "soy el punto" << endl;
                //location[i] =(int) atoi(punto);
                if (punto == '8') {                     //leemos los caracteres y verificamos que sean los deseados
                    location[i] = -1;
                    fprintf(file, "%d", 8);
                }
                if (punto == '0') {
                    location[i] = 0;
                    fprintf(file, "%d", 0);
                }
                if (punto == '1') {
                    location[i] = 1;
                    fprintf(file, "%d", 1);
                }
                if (punto == '2') {
                    location[i] = 2;
                    fprintf(file, "%d", 2);
                }
                if (punto == '3') {
                    location[i] = 3;
                    fprintf(file, "%d", 3);
                }
                if (punto == '4') {
                    location[i] = 4;
                    fprintf(file, "%d", 4);
                }
                if (punto == '5') {
                    location[i] = 5;
                    fprintf(file, "%d", 5);
                }
                if (punto == '6') {
                    location[i] = 6;
                    fprintf(file, "%d", 6);
                }
                if (punto == '7') {
                    location[i] = 7;
                    fprintf(file, "%d", 7);
                }
            }
            move_queens(location);
            fclose(file);
        }
        contador++;
        al_wait_for_event(event_queue, &events);
        al_get_keyboard_state(&keyState);
        eventsHandler();
        loop();
    }
    //



    al_destroy_display(display);//Liberar del display
    al_destroy_font(font);//Libera memoria de la letra*/

    return 0;
}