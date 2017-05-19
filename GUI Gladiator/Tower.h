#ifndef PRUEBAS_TOWER_H
#define PRUEBAS_TOWER_H

#include "Arrow.h"
#include "Gladiator.h"
#include <time.h>

class Tower : public Entity{
private:
    List<Arrow*> *arrows;
    List<Gladiator*> *targets;
    void Shot();
    char* target;
    int range=3, timer=0, shot=0;
public:
    Tower(char* resource,int row, int column, int width, int height, Map *m);
    ~Tower();
    void draw();
    void setTarget(char *target);
    void setRange(int range);
    void attack(Gladiator *entity);
    char* getTarget();
    int getRange();
};


#endif //PRUEBAS_TOWER_H
