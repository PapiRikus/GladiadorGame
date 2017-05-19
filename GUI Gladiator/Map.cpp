#include "Map.h"

Map::Map(int x,int y, int rows, int columns, int size_tiled){
    this->x=x;
    this->y=y;
    this->rows=rows;
    this->columns=columns;
    this->size_tiled=size_tiled;
    matrix = new Matrix<Tiled*>(rows,columns);
    bitmaps = new List<char*>();
}

void Map::addBitmap(char* resource){
    bitmaps->Insert(resource);
}

void Map::setBackground(char* map, char div_column, char div_row) {
    int temp = 0, temp_row = 0, temp_column = 0, u = 0, caracter = 0, integer = 0;
    while (temp < rows * columns) {
        if (map[caracter] == div_column) {
            matrix->addAt(temp_row, temp_column, new Tiled(bitmaps->Get(integer), x+temp_column*size_tiled, y+temp_row*size_tiled, size_tiled));
            cout << "setting on position " << temp_row << " " << temp_column << endl;
            temp_column++;
            u = 0;
            integer = 0;
            temp++;
        } else if (map[caracter] == div_row) {
            temp_row++;
            temp_column = 0;
        } else {
            integer += (map[caracter] - '0') * pow(10, u);
            u++;
        }
        caracter++;
    }
}

void  Map::draw() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix->getData(i,j)->draw();
        }
    }
}

void Map::setSolidTiledAt(int row, int column, int isSolid) {
    matrix->addAt(row, column, new Tiled(getTiledAt(row,column).getResource(), getTiledAt(row,column).getX(), getTiledAt(row,column).getY(), getTiledAt(row,column).getSize(), isSolid));
}

Tiled Map::getTiledAt(int row, int column) {
    return *matrix->getData(row,column);
}

int Map::getRows() { return rows; }
int Map::getColumns() { return columns; }
int Map::getX(){ return x; }
int Map::getY() { return y; }
int Map::getTiledSize() { return size_tiled; }