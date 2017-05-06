#ifndef PRUEBAS_GLADIATOR_H
#define PRUEBAS_GLADIATOR_H

#include "Entity.h"

class Gladiator : public Entity{
public:
    Gladiator(char* resource,int row, int column, int width, int height, Map *m);
    ~Gladiator();
    void draw();
};


#endif //PRUEBAS_GLADIATOR_H
