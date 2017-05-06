#ifndef PRUEBAS_TOWER_H
#define PRUEBAS_TOWER_H


#include "Entity.h"

class Tower : public Entity{
public:
    Tower(char* resource,int row, int column, int width, int height, Map *m);
    ~Tower();
    void draw();
    
};


#endif //PRUEBAS_TOWER_H
