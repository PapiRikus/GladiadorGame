//
// Created by richard on 26/04/17.
//

#include "VentanaAle.h"
VentanaAle::VentanaAle() {
    //backtrack = new backtracking();
    FILE *file;
    int location[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    //backtrack->bactrack8Queens(location,0,file,0);
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
  //  pthread_t hilo;
//    pthread_create(&hilo,NULL,this->loop,NULL);
}
/*void VentanaAle::eventsHandler(){
    //Evento que finaliza el loop al cerrar la ventana
    if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        run = false;
    }
}
*/
//Loop que dibuja y actualiza los componentes del juego
void* VentanaAle::loop(){
    while(true) {

        zone1->draw();
        for (int i = 0; i < queens->length(); ++i) {
            queens->Get(i)->draw();

        //move_queens(backtrack->location);
        al_draw_text(font, WHITE, screen_width/2, 0, ALLEGRO_ALIGN_CENTER,"soluciones de las 8 reinas: ");//Muestra texto en pantalla
        al_flip_display();//Refresca pantalla
        al_clear_to_color(GREY);//Repinta fondo
        }
    }
}
void VentanaAle::addQueen(int row, int column) {
    queens->Insert(new Queen("queen.png",row,column,zone1));
}
void VentanaAle::move_queens(int q[]){
    for (int i = 0; i < sizeof(q); ++i) {
        queens->Get(i)->moveAt(q[i],i);
    }
}