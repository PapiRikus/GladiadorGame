#include "Map.h"

Map::Map(int x,int y, int rows, int columns, int size_tiled){
    this->x=x;
    this->y=y;
    this->rows=rows;
    this->columns=columns;
    this->size_tiled=size_tiled;
    matrix = new Matrix<int>(rows,columns);
    bitmaps = new List<ALLEGRO_BITMAP*>();
}
void Map::addBitmap(char* resource){
    bitmaps->Insert(al_load_bitmap(resource));
}
void Map::setBackground(char* map, char div_column, char div_row) {
    int temp = 0, temp_row = 0, temp_column = 0, u = 0, caracter = 0, integer = 0;
    while (temp < rows * columns) {
        if (map[caracter] == div_column) {
            matrix->addAt(temp_row, temp_column, integer);
            cout << "setting: " << matrix->getData(temp_row, temp_column) << " on position " << temp_row << " "
                 << temp_column << endl;
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

int Map::getX(){
    return x;
}
int Map::getY() {
    return y;
}
int Map::getTiledSize() {
    return size_tiled;
}
void  Map::draw() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            al_draw_bitmap(bitmaps->Get(matrix->getData(i,j)),x+(size_tiled*j),y+(size_tiled*i),NULL);
        }
    }
}


