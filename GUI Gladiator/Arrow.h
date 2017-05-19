//
// Created by aaronsolera on 07/05/17.
//

#ifndef PRUEBAS_ARROW_H
#define PRUEBAS_ARROW_H


#include "Entity.h"

class Arrow : public Entity{
private:
    float damage = 0;
public:
    Arrow(char* bitmap,int row, int column, int width, int height, Map *m);
    ~Arrow();
    void draw();
    void setDamage(float damage);
    int getDamage();
};


#endif //PRUEBAS_ARROW_H
