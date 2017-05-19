//
// Created by aaronsolera on 28/04/17.
//

#include "Entity.h"

Entity::Entity(char* resourse, int row, int column, int width, int height,Map *m) {
    plane = m;
    bitmap = al_load_bitmap(resourse);
    x = m->getX()+(m->getTiledSize()*column)+(m->getTiledSize()/2-width/2);
    y = m->getY()+(m->getTiledSize()*row)+(m->getTiledSize()/2-height);
    sprite = new Sprite(resourse,x,y,width,height,1);
    tempX = x;
    tempY = y;
    this->width = width;
    this->height = height;
    this->current_column = column;
    this->current_row = row;
    sprite = new Sprite(resourse,x,y,width,height,1);
}

void Entity::moveAt(int row, int column) {
    if(row<0 or column<0 or row>plane->getRows()-1 or column>plane->getColumns()-1)
    {
        cout<<"Those coordinates does not exist"<<endl;
    }else if(!plane->getTiledAt(row,column).getIsSolid()){
        coor *c = new coor();
        c->startX=x;
        c->startY=y;
        c->column=x+(plane->getTiledSize()*(column-current_column));
        c->row=y+(plane->getTiledSize()*(row-current_row));
        if((column-current_column)!=0){
            c->x_direction=(column-current_column)/abs((int)(column-current_column));
        }
        if(current_column == column){
            c->degree = toRadians((row-current_row)/abs((int)(row-current_row))*90);
        }else{
            c->degree = atan((plane->getTiledSize()*(row-current_row))/(plane->getTiledSize()*(column-current_column)));
            if((column-current_column)<0) {
                c->y_direction = -1;
            }
        }
        c->path= sqrt(pow(plane->getTiledSize()*(row-current_row),2)+pow(plane->getTiledSize()*(column-current_column),2));
        current_column=column;
        current_row=row;
        x = c->column;
        y = c->row;
        movements->Insert(c);
    } else {
        cout<<"That cell is occupied"<<endl;
    }
}

void Entity::moving(){
    if(!movements->isEmpty()){
        if(movements->Get(0)->temp_path < movements->Get(0)->path+1){
            tempX = (int) (movements->Get(0)->startX + (movements->Get(0)->x_direction) * (movements->Get(0)->temp_path * cos(movements->Get(0)->degree)));
            tempY = (int) (movements->Get(0)->startY + (movements->Get(0)->y_direction) * (movements->Get(0)->temp_path * sin(movements->Get(0)->degree)));
            movements->Get(0)->temp_path+=speed;
            for (int s = 0; s < sprite->animations->length(); ++s) {
                if ((movements->Get(0)->x_direction) < 0) {
                    if (sprite->animations->Get(s)->id == "LEFT") {
                        sprite->setAnimation("LEFT");
                    }
                } else if ((movements->Get(0)->x_direction) > 0) {
                    if (sprite->animations->Get(s)->id == "RIGHT") {
                        sprite->setAnimation("RIGHT");
                    }
                }
                if (sin(movements->Get(0)->degree) < 0) {
                    if (sprite->animations->Get(s)->id == "UP") {
                        sprite->setAnimation("UP");
                    }
                } else if (sin(movements->Get(0)->degree) > 0) {
                    if (sprite->animations->Get(s)->id == "DOWN") {
                        sprite->setAnimation("DOWN");
                    }
                }
            }
        }else{
            cout<<"A movement has been deleted"<<endl;
            movements->Delete(0);
            sprite->setAnimation("DEFAULT");
        }
    }
}

void Entity::draw(){
    sprite->setX(tempX);
    sprite->setY(tempY);
    sprite->draw();
}
void Entity::addAnimation(char* id, int row, int column) { sprite->insertAnimation(id, row, column); }
void Entity::setSpeed(float speed) { this->speed = (0.1f) * speed; }
void Entity::setAnimation(char* id) { sprite->setAnimation(id); }
void Entity::setPosition(int row, int column) {
    this->tempX = plane->getX()+(plane->getTiledSize()*column)+(plane->getTiledSize()/2-width/2);
    this->tempY = plane->getY()+(plane->getTiledSize()*row)+(plane->getTiledSize()/2-height);
    this->x = tempX;
    this->y = tempY;
    this->current_column=getCurrentColumn();
    this->current_row=getCurrentRow();
}
int Entity::getEndPathRow() { return current_row; }
int Entity::getEndPathColumn() { return current_column; }
int Entity::getCurrentRow() { return (int)((tempY-plane->getY()) + height)/ plane->getTiledSize(); }
int Entity::getCurrentColumn() { return (int)(tempX-plane->getX()) / plane->getTiledSize(); }
int Entity::getX() { return tempX; }
int Entity::getY() { return tempY; }
double Entity::toRadians(int degree) { return (degree*(PI/180)); }
Entity::~Entity() {}