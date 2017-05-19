#ifndef PRUEBAS_MAP_H
#define PRUEBAS_MAP_H

#include <iostream>
#include "Matrix.h"
#include <math.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

class Map {
private:
    int x, y, rows, columns, size_tiled;
    Matrix<int> *matrix;
    ALLEGRO_BITMAP *tiled;
    List<ALLEGRO_BITMAP*> *bitmaps;
public:
    Map(int x, int y, int rows, int columns, int size_tiled);
    ~Map();
    void draw();
    int getTiledSize();
    int getX();
    int getY();
    void setBackground(char* map, char div_column, char div_row);
    void addBitmap(char* resource);
};


#endif
