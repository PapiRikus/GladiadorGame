#ifndef PRUEBAS_GLADIATOR_H
#define PRUEBAS_GLADIATOR_H
#define WHITE al_map_rgb(255,255,255)
#define LIGHT_BLUE al_map_rgb(51, 153, 255)
#include "Entity.h"

class Gladiator : public Entity{
private:
    ALLEGRO_FONT *font;
    string name = "nameless";
    int hand_damage = 0, foot_damage = 0, body_to_body_damage = 0, hand_resistance = 0, foot_resistance = 0, body_to_body_resistance = 0, total_resistance = 0, original_resistance=0;
public:
    Gladiator(char* resource,int row, int column, int width, int height, Map *m);
    ~Gladiator();
    void draw();
    void setName(string name), setHandDamage(int damage), setFootDamage(int damage), setBodyDamage(int damage), setHandResistance(int resistance), setFootResistance(int resistance), setBodyResistance(int resistance), setTotalResistance(int resistance), hurt(int damage), drawResistanceBar();
    string getName();
    int getHandDamage(), getFootDamage(), getBodyDamage(), getHandResistance(), getFootResistance(), getBodyResistance(), getTotalResistance();
};


#endif //PRUEBAS_GLADIATOR_H
