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
    sprite->insertAnimation("none",0,1);
    sprite->insertAnimation("right",0,4);
    sprite->insertAnimation("left",1,4);
    sprite->insertAnimation("down",2,4);
    sprite->insertAnimation("up",3,4);
    sprite->setAnimation("none");
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
        }
        c->path= sqrt(pow(plane->getTiledSize()*(row-current_row),2)+pow(plane->getTiledSize()*(column-current_column),2));
        current_column=column;
        current_row=row;
        x = c->column;
        y = c->row;
        movements->Insert(c);
        cout<<"Hipo: "<<c->path<<"\n"<<"Degree: "<<c->degree<<"\n"<<"Degree cos(): "<<cos(c->degree)<<"\n"<<" Degree sin(): "<<sin(c->degree)<<endl;
    } else {
        cout<<"That cell is occupied"<<endl;
    }
}

void Entity::moving(){
    if(!movements->isEmpty()){
        if(movements->Get(0)->temp_path < movements->Get(0)->path+1){
            tempX = (int) (movements->Get(0)->startX + (movements->Get(0)->x_direction) * (movements->Get(0)->temp_path * cos(movements->Get(0)->degree)));
            tempY = (int) (movements->Get(0)->startY + (movements->Get(0)->temp_path * sin(movements->Get(0)->degree)));
            movements->Get(0)->temp_path++;
            cout<<"Current position: "<<tempX<<" "<<tempY<<endl;
            if((movements->Get(0)->x_direction)<0){
                sprite->setAnimation("left");
            }else if((movements->Get(0)->x_direction)>0){
                sprite->setAnimation("right");
            }else if(sin(toRadians(movements->Get(0)->degree))<0){
                sprite->setAnimation("up");
            }else{
                sprite->setAnimation("down");
            }
        }else{
            cout<<"A movement has been deleted"<<endl;
            movements->Delete(0);
            cout<<"Current Row: "<<getCurrentRow()<<"\n"<<"Current Column: "<<getCurrentColumn()<<endl;
        }
    }else{
        sprite->setAnimation("none");
    }
}

void Entity::draw(){
    sprite->setX(tempX);
    sprite->setY(tempY);
    sprite->draw();
}

int Entity::getEndPathRow() { return current_row; }
int Entity::getEndPathColumn() { return current_column; }
int Entity::getCurrentRow() { return (int)((tempY-plane->getY()) + height)/ plane->getTiledSize(); }
int Entity::getCurrentColumn() { return (int)(tempX-plane->getX()) / plane->getTiledSize(); }
double Entity::toRadians(int degree) { return (degree*(PI/180)); }
Entity::~Entity() {}