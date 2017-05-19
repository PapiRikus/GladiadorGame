#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include "Gladiator.h"
#include "Tower.h"
#include "PathfindingA.h"
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include "SeleccionMJ.h"
#include "Botones.h"
#include "IA.h"
#include "gladiador.h"
//Constantes definidas (Colores, dimensiones, medidas, entre otros)
#define screen_width 800
#define screen_height 600
#define SAND al_map_rgb(225, 204, 79)
#define WHITE al_map_rgb(255, 255, 255)
#define FPS 60.0

using namespace std;

bool run=true;//Booleano que ejecuta el loop
bool pressed = false, stop = false;

int mouseX = 0, mouseY = 0;//variables para obtener la posicion del mouse
ALLEGRO_DISPLAY *display;//Variable global ventana, se utiliza para mostrar el juego
ALLEGRO_EVENT_QUEUE *event_queue;//Variable de la cola de eventos
ALLEGRO_FONT *font;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT events;
ALLEGRO_BITMAP *player_sprite;
ALLEGRO_KEYBOARD_STATE keyState;
Map *zone1, *zone2;
Gladiator *gladiator1, *gladiator2;
PathfindingA *pathfinding;
int** zoneSolids = new int*[5];//Da los sólidos de la zona
List<Tower*> *towers = new List<Tower*>();
int generation=1, victorys1=0, victorys2=0, fitness, fitness_average, mutations, n_mutations;


int ganador = -1;
gladiador *gladiador1;
gladiador *gladiador2;
Botones   *Btns;
IA *Ia;
SeleccionMJ *seleccionMJ;
ALLEGRO_BITMAP *bitmap;
ALLEGRO_BITMAP *bitmapGladiadoresApoyando;



void setSolidMatrix(Map *zone){
    for (int row = 0; row < 5; ++row) {
        for (int column = 0; column < 10; ++column){
            zoneSolids[row][column] = zone->getTiledAt(row, column).getIsSolid();
            cout<<zone->getTiledAt(row, column).getIsSolid();
        }
        cout<<endl;
    }
}

void calculatePath(Entity *entity, Map *map) {
    setSolidMatrix(map);
    PList<PList<int>> path = pathfinding->getPath(zoneSolids, map->getRows(), map->getColumns(), entity->getCurrentRow(), entity->getCurrentColumn(), 2, 9);
    for (int m = 0; m < path.size(); ++m) {
        entity->moveAt(path.get(m).get(0), path.get(m).get(1));
    }
}

void addTowers(Map *zone, Gladiator *gladiator){
    int r, c, t = 0;
    setSolidMatrix(zone);
    while(t<3) {
        r = rand() % zone->getRows();
        c = rand() % zone->getColumns();
        if (zoneSolids[r][c] != 1 && !(r == 2 & (c == 0 || c == 9))) {
            zoneSolids[r][c] = 1;
            if (!pathfinding->getPath(zoneSolids, zone->getRows(), zone->getColumns(), gladiator->getCurrentRow(), gladiator->getCurrentColumn(), 2, 9).isEmpty()) {
                towers->Insert(new Tower("tower.png", r, c, 50, 70, zone));
                towers->Get(towers->length() - 1)->attack(gladiator);
                towers->Get(towers->length() - 1)->setRange(1);
                zone->setSolidTiledAt(r, c, 1);
            }
            t++;
        }
    }
}

void drawTowers(){
    for (int t = 0; t < towers->length(); ++t) {
        towers->Get(t)->draw();
    }
}

//Inicialización de todos los componentas para el juego, aquí deben definirse las variables
void initialize(){
    al_init();//Inicia componentes básicos para usar alegro
    al_init_font_addon();//Inicializa los formato de letra
    al_init_ttf_addon();//Inicializa los archivos de tipos de letras
    al_init_primitives_addon();//Inicializa formas primitivas(rectángulos, triángulos, círculos, entre otros)
    al_install_keyboard();//Inicializa el teclado
    al_install_mouse();// instalamos las operaciones con el mouse
    al_init_image_addon();//Inicializa imagenes

    font = al_load_font("game_font.ttf", 12, NULL);//Establece el formato de letra
    display = al_create_display(screen_width, screen_height);//Crea ventana con dimensiones
    timer = al_create_timer(1.0/FPS);//Temporizador de frames del loop
    event_queue = al_create_event_queue();//Cola de eventos (del teclado, mouse, display, etc)
    player_sprite = al_load_bitmap("gladiator_negro.png");//Establece una imagen al bitmap
    pathfinding = new PathfindingA();

    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_keyboard_event_source());//Registra los eventos de teclado en la cola
    al_register_event_source(event_queue,al_get_display_event_source(display));//Registrando eventos display en la cola
    al_register_event_source(event_queue,al_get_timer_event_source(timer));//Registra evento del temporizador en la cola
    al_start_timer(timer);//Inicia el temporizador del loop
    srand(time(NULL));
    //inicializador del arreglo de los sólidos
    for (int r = 0; r < 5; ++r) {
        zoneSolids[r] = new int[10];
    }
    zone1 = new Map(50,50,5,10,50);
    zone2 = new Map(50,300,5,10,50);
    zone1->addBitmap("sand.png");
    zone1->addBitmap("white_cell.png");
    zone2->addBitmap("dirt.png");
    zone2->addBitmap("white_cell.png");
    char* map="0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,/0,0,0,0,0,0,0,0,0,0,";
    zone1->setBackground(map,',','/');
    zone2->setBackground(map,',','/');
    gladiator1 = new Gladiator("gladiator_negro.png", zone1->getRows()/2, 0, 40, 40, zone1);
    gladiator1->addAnimation("RIGHT",0,3);
    gladiator1->addAnimation("LEFT",1,3);
    gladiator1->addAnimation("DOWN",2,3);
    gladiator1->addAnimation("UP",3,3);
    gladiator1->addAnimation("DEATH",4,1);
    gladiator2 = new Gladiator("gladiator_blanco.png", zone1->getRows()/2, 0, 40, 40, zone2);
    gladiator2->addAnimation("RIGHT",0,3);
    gladiator2->addAnimation("LEFT",1,3);
    gladiator2->addAnimation("DOWN",2,3);
    gladiator2->addAnimation("UP",3,3);
    gladiator2->addAnimation("DEATH",4,1);
    addTowers(zone1, gladiator1);
    calculatePath(gladiator1, zone1);
    addTowers(zone2, gladiator2);
    calculatePath(gladiator2, zone2);



    //extra
    Ia = new IA();
    gladiador1  = new gladiador("peleador.png",100,200,10,50,50,50,5,7,2);
    gladiador1->setTurno(true);
    gladiador2  = new gladiador("peleadorDark.png",200,200,10,60,40,50,3,5,8);
    Btns        = new Botones("Botones.png",50,400,gladiador1,gladiador2);
    seleccionMJ = new SeleccionMJ("selectPeleador.png",100,250);
    bitmap =  (ALLEGRO_BITMAP *)al_load_bitmap("stdium.jpg");
    bitmapGladiadoresApoyando = (ALLEGRO_BITMAP *)al_load_bitmap("Pancartas.png");

}

//Manejador de eventos. Aquí se establecen y administran eventos de teclado, mouse, display, entre otros.
void eventsHandler(){
    //Evento que finaliza el loop al cerrar la ventana
    if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        run = false;
    }
}
void drawStadistics(const char* num_generations,const char* victorys_gladiator1,const char* victorys_gladiator2,const char* fitness, const char* fitness_average, const  char* mutations_probability, const char* number_of_mutations){
    char n[50] = "generaciones transcurridas: ";
    strcat(n,num_generations);
    al_draw_text(font, WHITE, screen_width/2, screen_height/4, ALLEGRO_ALIGN_CENTER, n);
    char c[50] ="victorias del galdiador blanco: ";
    strcat(c,victorys_gladiator1);
    al_draw_text(font, WHITE, screen_width/2, screen_height/4+20, ALLEGRO_ALIGN_CENTER, c);
    char t[50] ="victorias del galdiador negro: ";
    strcat(t,victorys_gladiator2);
    al_draw_text(font, WHITE, screen_width/2, screen_height/4+40, ALLEGRO_ALIGN_CENTER, t);
    char f[50] ="fitness: ";
    strcat(f,fitness);
    al_draw_text(font, WHITE, screen_width/2, screen_height/4+60, ALLEGRO_ALIGN_CENTER, f);
    char fp[50] ="fitness promedio: ";
    strcat(fp,fitness_average);
    al_draw_text(font, WHITE, screen_width/2, screen_height/4+80, ALLEGRO_ALIGN_CENTER, fp);
    char m[50] ="probabilidad de mutaciones: ";
    strcat(m,mutations_probability);
    al_draw_text(font, WHITE, screen_width/2, screen_height/4+100, ALLEGRO_ALIGN_CENTER, m);
    char nm[50] ="numero de mutaciones: ";
    strcat(nm,number_of_mutations);
    al_draw_text(font, WHITE, screen_width/2, screen_height/4+120, ALLEGRO_ALIGN_CENTER, nm);
}

void reset(){
    gladiator1->setPosition(zone1->getRows()/2, 0);
    addTowers(zone1,gladiator1);
    calculatePath(gladiator1,zone1);
    gladiator2->setPosition(zone2->getRows()/2, 0);
    addTowers(zone2,gladiator2);
    calculatePath(gladiator2,zone2);
    generation++;
    cout<<"reseteoo!!!!!!!!!!!!!!!!!!"<<endl;
}

//Loop que dibuja y actualiza los componentes del juego
void mapLoop() {
    if (events.type == ALLEGRO_EVENT_TIMER) {
        zone1->draw();
        zone2->draw();
        gladiator1->draw();
        gladiador1->setgladiador(gladiator1->getTotalResistance(),gladiator1->getHandResistance(),gladiator1->getFootResistance(),gladiator1->getBodyResistance(),gladiator1->getHandDamage(),gladiator1->getFootDamage(),gladiator1->getBodyDamage());
        gladiador1->setTurno(true);
        gladiator2->draw();
        gladiador2->setgladiador(gladiator2->getTotalResistance(),gladiator2->getHandResistance(),gladiator2->getFootResistance(),gladiator2->getBodyResistance(),gladiator2->getHandDamage(),gladiator2->getFootDamage(),gladiator1->getBodyDamage());
        gladiador2->setTurno(false);
        drawTowers();
        al_draw_text(font, WHITE, 0, 0, ALLEGRO_ALIGN_LEFT, to_string(generation).c_str());
        al_draw_text(font, WHITE, 0, screen_height-screen_height/32, ALLEGRO_ALIGN_LEFT, "genetic gladiator");
        al_flip_display();
        al_clear_to_color(SAND);
    }
}

void Post(string data){
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    struct curl_slist *headers=NULL; // init to NULL is important

    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");

    curl = curl_easy_init();
    if(curl) {

        //  std::string data4 = "{\"nombre\"😕"Rober\"}";
        // std::cout<<data4<<" Esto es data 4 json";
        string data1 = "{\"nombre\":\"";

        string data2 = "\"}";
        cout<< "esto ";

        data1.append(data);
        data1.append(data2);
        cout<<data1<<"Esto es data 1";


        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.100.7:8080/GeneticServer2/webapi/Gladiator/set");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,data1.c_str() );

//    curl_easy_setopt(curl, CURLOPT_HTTPGET,1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);

        if(CURLE_OK == res) {
            char *ct;
            /* ask for the content-type */
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
            if((CURLE_OK == res) && ct)
                printf("We received Content-Type: %s\n", ct);
        }
    }
}

void loopPelea(){


    if(events.type==ALLEGRO_EVENT_TIMER){
        /*
         * codigo a implementar con la parte de aaron
         * realizado por Richard Guillen Varela
         */
        std::cout<<gladiador1->getVida()<<"vida"<<std::endl;
        if(gladiador1->getVida()<=0){
            ganador = 1;
            stop  = true;
        }else if(gladiador2->getVida()<=0){
            ganador = 2;
            stop = true;
        }

        if(seleccionMJ->getEstado()==true) {

            al_draw_bitmap_region(bitmap,0,0,500,500,0,0,NULL);
            int localPY = 0;                            // esta variable lo que realiza es almacenar la posicion de los bichitos de atras
            int pxGladiadorNegro = 260;
            int pxGladiadorBlanco = 30;
            for (int j = 0; j < 4; ++j) {
                if(gladiador2->getEstado()==-1) {
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 0, 0, 50, 75, pxGladiadorNegro + (j * 50), localPY, NULL);
                }else if(gladiador2->getEstado()==0){
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 50, 0, 50, 75, pxGladiadorNegro + (j * 50), localPY, NULL);
                }else if(gladiador2->getEstado()==1){
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 100, 0, 50, 75, pxGladiadorNegro + (j * 50), localPY, NULL);
                }else if(gladiador2->getEstado()==2){
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 150, 0, 50, 75, pxGladiadorNegro + (j * 50), localPY, NULL);
                }

                if(gladiador1->getEstado()==-1){
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 0, 75, 50, 75, pxGladiadorBlanco + (j * 50), localPY, NULL);
                }else if(gladiador1->getEstado()==0){
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 50, 75, 50, 75, pxGladiadorBlanco + (j * 50), localPY, NULL);
                }else if(gladiador1->getEstado()==1){
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 100, 75, 50, 75, pxGladiadorBlanco + (j * 50), localPY, NULL);
                }else if(gladiador1->getEstado()==2){
                    al_draw_bitmap_region(bitmapGladiadoresApoyando, 150, 75, 50, 75, pxGladiadorBlanco + (j * 50), localPY, NULL);
                }
            }



            if(seleccionMJ->getMetodoJuego()==1){
                Ia->calcularGolpe(gladiador1,gladiador2);
            }else if(seleccionMJ->getMetodoJuego()==2){
                Ia->calcularGolpe(gladiador1,gladiador2);
                Ia->calcularGolpe(gladiador2,gladiador1);
            }


            Btns->draw(mouseX, mouseY);
            gladiador1->draw();
            gladiador2->draw();

            al_draw_text(font, WHITE, screen_width / 2, 0, ALLEGRO_ALIGN_CENTER, "lucha de gladiadores: ");//Muestra texto en pantalla



        }else{
            seleccionMJ->draw();

        }
        al_flip_display();//Refresca pantalla
    }
        /**
         * codigo a implementar en la progra, realizado por richard Guillen Varela
         *
         * */

    else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        mouseY = events.mouse.y;
        mouseX = events.mouse.x;
        if(seleccionMJ->getEstado()==true) {
            Btns->presionMouse(mouseX, mouseY);
        }else{
            seleccionMJ->mousePresionado(mouseX,mouseY);
        }
    }else if(events.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouseY = events.mouse.y;
        mouseX = events.mouse.x;
    }
}


void figthLoop(){
    al_flip_display();//Refresca pantalla
    al_clear_to_color(SAND);//Repinta fondo
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void get(Gladiator *gladiator, char* URL_id) {
    CURL *curl;
    CURLcode res;
    string readBuffer;
    curl = curl_easy_init();

    if(curl){
        if(URL_id=="popuA"){
            curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.100.7:8080/GeneticServer2/webapi/Gladiator/popuA");
        }else if(URL_id=="popuB"){
            curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.100.7:8080/GeneticServer2/webapi/Gladiator/popuB");
        }else{
            cout<<"No es posible obtener los datos"<<endl;
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        cout<< res;
        cout << readBuffer << endl;

        Json::Value root;
        Json::Reader reader;
        cout<< "estoo";
        bool parsingSuccessful = reader.parse( readBuffer.c_str(), root );     //parse process
        if( !parsingSuccessful ){
            cout<<"Error"<<endl;
        } else{
            string name = root.get("nombre", "A Default Value if not exists" ).asString().c_str();
            gladiator->setName(name);
            gladiator->setFootDamage(atoi(root.get("golpePies", "A Default Value if not exists" ).asString().c_str()));
            gladiator->setBodyDamage(atoi(root.get("golpeCuerpo", "A Default Value if not exists" ).asString().c_str()));
            gladiator->setHandDamage(atoi(root.get("golpeMano", "A Default Value if not exists" ).asString().c_str()));
            gladiator->setFootResistance(atoi(root.get("resistencaGolpesPies", "A Default Value if not exists" ).asString().c_str()));
            gladiator->setHandResistance(atoi(root.get("resistenciaColpesMano", "A Default Value if not exists" ).asString().c_str()));
            gladiator->setBodyResistance(atoi(root.get("resistenciaGolpesCuerpo", "A Default Value if not exists" ).asString().c_str()));
            gladiator->setTotalResistance(atoi(root.get("resistenciaTotal", "A Default Value if not exists" ).asString().c_str()));
        }
    }
}





int main() {
    initialize();
    get(gladiator1, "popuA");
    get(gladiator2, "popuB");
    while(run) {
        al_wait_for_event(event_queue, &events);
        al_get_keyboard_state(&keyState);
        eventsHandler();
        if(!gladiator1->movements->isEmpty() or !gladiator2->movements->isEmpty()){
            mapLoop();
            if(gladiator1->getTotalResistance()<=0){
                ganador=1;
                stop=true;
            }if(gladiator1->getTotalResistance()<=0){
                ganador=2;
                stop=true;
            }else{
                ganador=0;
            }
        }else{
            if(!stop){
                if(gladiator1->getTotalResistance()!=0 & gladiator2->getTotalResistance()!=0){
                    loopPelea();
                }else{
                    stop=true;
                }
            }else{
                drawStadistics( to_string(generation).c_str(), to_string(victorys1).c_str(), to_string(victorys2).c_str(), "", "", "", "");
                al_flip_display();
                al_clear_to_color(SAND);
            }
            if (al_key_down(&keyState, ALLEGRO_KEY_SPACE)) {
                if (!pressed) {
                    stop = false;
                    if(ganador==1){
                        Post(gladiator2->getName());
                        victorys1++;
                    }
                    if(ganador==2){
                        Post(gladiator1->getName());
                        victorys2++;
                    }
                    get(gladiator1, "popuA");
                    get(gladiator2, "popuB");
                    reset();
                    pressed = true;
                }
            } else {
                pressed = false;
            }
        }
    }
    al_destroy_bitmap(player_sprite);//Libera memoria de los bitmaps
    al_destroy_display(display);//Liberar del display
    al_destroy_font(font);//Libera memoria de la letra

    return 0;
}