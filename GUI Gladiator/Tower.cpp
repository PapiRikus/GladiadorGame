//
// Created by aaronsolera on 28/04/17.
//

#include "Tower.h"

Tower::Tower(char *resource, int row, int column, int width, int height, Map *m) : Entity(resource,row,column,width,height,m) {
    plane->setSolidTiledAt(row, column, 1);
    arrows = new List<Arrow*>();
    targets = new List<Gladiator*>();
}
void Tower::draw() {
    Entity::draw();
    Shot();
}

void Tower::attack(Gladiator *entity){
    targets->Insert(entity);
}

void Tower::Shot() {
    for (int r = 0; r < ((range*2)+1); ++r) {
        for (int c = 0; c < ((range * 2) + 1); ++c) {
            if(((getCurrentRow() - (range)) + r)>=0 & ((getCurrentRow() - (range)) + r)<plane->getRows() & ((getCurrentColumn() - (range)) + c)>=0 & ((getCurrentColumn() - (range)) + c)<plane->getColumns()){
                for (int o = 0; o < targets->length(); ++o) {
                    shot=rand()%51;
                    if (timer%50==0 & targets->Get(o)->getCurrentRow() == (getCurrentRow() - (range)) + r & targets->Get(o)->getCurrentColumn() == (getCurrentColumn() - (range)) + c & targets->Get(0)->getTotalResistance()>0 & !(targets->Get(o)->getCurrentRow()==2 & targets->Get(o)->getCurrentColumn()==9)){
                        arrows->Insert(new Arrow("arrow.png", getCurrentRow() - 1, getCurrentColumn(), 20, 20, plane));
                        arrows->Get(arrows->length() - 1)->setDamage(5);
                        arrows->Get(arrows->length() - 1)->addAnimation("LEFT", 0, 1);
                        arrows->Get(arrows->length() - 1)->addAnimation("DOWN", 1, 1);
                        arrows->Get(arrows->length() - 1)->addAnimation("RIGHT", 2, 1);
                        arrows->Get(arrows->length() - 1)->addAnimation("UP", 3, 1);
                        arrows->Get(arrows->length() - 1)->addAnimation("DEFAULT", 4, 1);
                        arrows->Get(arrows->length() - 1)->moveAt((getCurrentRow() - (range)) + r, (getCurrentColumn() - (range)) + c);
                    }
                }
            }
        }
    }
    if(!arrows->isEmpty()){
        if(arrows->Get(0)->getEndPathRow() == arrows->Get(0)->getCurrentRow() & arrows->Get(0)->getEndPathColumn() == arrows->Get(0)->getCurrentColumn() & timer%50 == 0){
            arrows->Delete(0);
            timer=0;
        }
    }
    for (int a = 0; a < arrows->length(); ++a){
        arrows->Get(a)->draw();
        for (int e = 0; e < targets->length(); ++e) {
            if(arrows->Get(a)->getCurrentRow() == targets->Get(e)->getCurrentRow() & arrows->Get(a)->getCurrentColumn() == targets->Get(e)->getCurrentColumn() & arrows->Get(a)->getDamage() != 0){
                targets->Get(0)->hurt(arrows->Get(a)->getDamage());
                arrows->Get(a)->setDamage(0);
            }
        }
    }
    timer++;
}

void Tower::setTarget(char *target) { this->target = target; }
void Tower::setRange(int range) { this->range = range; }
char* Tower::getTarget(){ return target; }
int Tower::getRange() { return range; }
