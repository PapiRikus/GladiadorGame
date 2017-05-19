//
// Created by aaronsolera on 23/04/17.
//

#ifndef PRUEBAS_QUEEN_H
#define PRUEBAS_QUEEN_H


#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include "Map.h"

class Queen {
private:
    ALLEGRO_BITMAP *bitmap;
    int x,y;
    struct coor{
        int row;
        int colum;
    };
    List<coor> *movements = new List<coor>();
    Map *plane;
public:
    Queen(char* bitmap,int row, int column, Map *m);
    ~Queen();
    void moveAt(int row, int collumn);
    void draw();
};



#endif //PRUEBAS_QUEEN_H
