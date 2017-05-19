//
// Created by aaronsolera on 08/05/17.
//

#ifndef PRUEBAS_NODE_H
#define PRUEBAS_NODE_H
#include "PList.h"

class Node {

private:
    //Attributes
    int _posI;
    int _posJ;
    bool _walkable;
    int _costG;
    double _costH;
    double _costF;
    Node* _previous;
    PList<Node*>* _neighbors;

public:

    Node(int, int, bool);
    virtual ~Node();

    int getPosI() const;
    void setPosI(int);

    int getPosJ() const;
    void setPosJ(int);

    bool getWalkable() const;
    void setWalkable(bool);

    int getCostG() const;
    void setCostG(int);

    double getCostH() const;
    void setCostH(double);

    double getCostF() const;
    void setCostF(double);

    Node* getPreviousNode() const;
    void setPreviousNode(Node*);

    void addNeighbors(Node***, int, int);

    PList<Node*>* getNeighbors() const;

};

#endif //PRUEBAS_NODE_H
