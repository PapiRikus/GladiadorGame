//
// Created by aaronsolera on 08/05/17.
//

#ifndef PRUEBAS_PATHFINDINGA_H
#define PRUEBAS_PATHFINDINGA_H
#include <iostream>
#include "Node.h"
#include <cmath>
using namespace std;
class PathfindingA {
private:
    //Attributes
    Node*** _nodeMap;
    PList<Node*>* _openSet;
    PList<Node*>* _closeSet;
    PList<Node*>* _path;

    //Methods
    double calculateHeuristics(Node*, Node*);
    bool inOpenSet(Node*);
    bool inCloseSet(Node*);
    void initiateNodesMap(int**, int, int);
    void cleanLists();
public:
    PathfindingA();
    ~PathfindingA();
    PList<PList<int>> getPath(int**, int, int, int, int, int, int);
};
#endif //PRUEBAS_PATHFINDINGA_H
