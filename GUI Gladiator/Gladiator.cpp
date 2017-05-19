//
// Created by aaronsolera on 22/04/17.
//

#include "Gladiator.h"
#include <allegro5/allegro_primitives.h>

Gladiator::Gladiator(char* resource, int row, int column, int width, int height,Map *m)  : Entity(resource,row,column,width,height,m){
    setSpeed(5);
    font = al_load_font("game_font.ttf", 5, NULL);
}

void Gladiator::hurt(int damage) {
    if(total_resistance>0){
        total_resistance-=damage;
    }
}

void Gladiator::drawResistanceBar() {
    al_draw_filled_rectangle(getX(), getY()-height/10, getX()+(((float)total_resistance/(float)original_resistance))*(width), getY(), LIGHT_BLUE);
}

void Gladiator::draw(){
    Entity::moving();
    Entity::draw();
    drawResistanceBar();
    al_draw_text(font, WHITE, getX()+width/2, getY()-height/3, ALLEGRO_ALIGN_CENTER, getName().c_str());
    if(total_resistance<=0){
        setAnimation("DEATH");
        movements->clear();
    }
}

void Gladiator::setName(string name) { this->name = name; }
void Gladiator::setBodyDamage(int damage) { this->body_to_body_damage=damage; }
void Gladiator::setHandDamage(int damage) { this->hand_damage = damage; }
void Gladiator::setFootDamage(int damage) { this->foot_damage = damage; }
void Gladiator::setBodyResistance(int resistance) { this->body_to_body_resistance = resistance; }
void Gladiator::setHandResistance(int resistance) { this->hand_resistance = resistance; }
void Gladiator::setFootResistance(int resistance) { this->foot_resistance = resistance; }
void Gladiator::setTotalResistance(int resistance) { this->total_resistance = resistance; original_resistance=total_resistance; }
string Gladiator::getName() { return name; }
int Gladiator::getBodyDamage() { return body_to_body_damage; }
int Gladiator::getHandDamage() { return  hand_damage; }
int Gladiator::getFootDamage() { return foot_damage; }
int Gladiator::getBodyResistance() { return body_to_body_resistance; }
int Gladiator::getHandResistance() { return  hand_resistance; }
int Gladiator::getFootResistance() { return foot_resistance; }
int Gladiator::getTotalResistance() { return total_resistance; }