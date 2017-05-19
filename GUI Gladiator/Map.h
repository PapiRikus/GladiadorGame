#ifndef PRUEBAS_MAP_H
#define PRUEBAS_MAP_H

#include <iostream>
#include <math.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Tiled.h"

using namespace std;

class Map {
private:
    int x, y, rows, columns, size_tiled;
    Matrix<Tiled*> *matrix;
    ALLEGRO_BITMAP *tiled;
    List<char*> *bitmaps;
public:
    Map(int x, int y, int rows, int columns, int size_tiled);
    ~Map();
    void draw();
    int getTiledSize();
    int getX();
    int getY();
    int getRows();
    int getColumns();
    Tiled getTiledAt(int row, int column);
    void setSolidTiledAt(int row, int column, int isSolid);
    void setBackground(char* map, char div_column, char div_row);
    void addBitmap(char* resource);
};


#endif
