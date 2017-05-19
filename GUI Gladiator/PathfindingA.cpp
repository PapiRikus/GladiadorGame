//
// Created by aaronsolera on 08/05/17.
//
#include "PathfindingA.h"

PathfindingA::PathfindingA() {
    this->_openSet = new PList<Node*>();
    this->_closeSet = new PList<Node*>();
    this->_path = new PList<Node*>();
}

PathfindingA::~PathfindingA() {

}

/**
 * Function that calculates the heuristic (estimate of the cost of the most economical path) of the distance of two nodes
 *
 * @param pStartNode - The initial node
 * @param pEndNode - The final node
 * @return - The distance between the nodes (estimated cost)
 */
double PathfindingA::calculateHeuristics(Node* pStartNode, Node* pEndNode) {

    //Euclidean distance
    int x = pEndNode->getPosI() - pStartNode->getPosI();
    int y = pEndNode->getPosJ() - pStartNode->getPosJ();

    return std::sqrt((x*x) + (y*y));

}

/**
 * Function that searches for a node in the openSet list
 *
 * @param pNode - The node to search
 * @return - If the node is in the openSet list
 */
bool PathfindingA::inOpenSet(Node* pNode) {

    //Search for the node in the whole list
    for(int i = 0; i < this->_openSet->size(); i++) {
        //Found the desired node
        if(this->_openSet->get(i) == pNode)
            return true;
    }
    //Not found the desired node
    return false;
}

/**
 * Function that searches for a node in the closeSet list
 *
 * @param pNode - The node to search
 * @return - If the node is in the closeSet list
 */
bool PathfindingA::inCloseSet(Node* pNode) {

    //Search for the node in the whole list
    for(int i = 0; i < this->_closeSet->size(); i++) {
        //Found the desired node
        if(this->_closeSet->get(i) == pNode)
            return true;
    }
    //Not found the desired node
    return false;

}

/**
 * Function that converts an array of numbers to an array of nodes, and thus apply a  A* Pathfinding algorithm
 *
 * @param pMap - The map of the game, indicating valid points to pass (where there are obstacles and not)
 * @param pRows - The number of rows of the received matrix
 * @param pColumns - The number of columns of the received matrix
 */
void PathfindingA::initiateNodesMap(int** pMap, int pRows, int pColumns) {

    //Create the array of nodes
    this->_nodeMap = new Node**[pRows];
    for(int i = 0; i < pRows; i++) {
        this->_nodeMap[i] = new Node*[pColumns];
    }

    //Fill the matrix with nodes
    for(int i = 0; i < pRows; i++) {
        for(int j = 0; j < pColumns; j++) {
            this->_nodeMap[i][j] = new Node(i, j, pMap[i][j]);
        }
    }

    //Established the neighbors of each node in the matrix
    for(int i = 0; i < pRows; i++) {
        for(int j = 0; j < pColumns; j++) {
            this->_nodeMap[i][j]->addNeighbors(this->_nodeMap, pRows, pColumns);
        }
    }
/*
    int i = 2;
    int j = 0;

    for(int k = 0; k < this->_nodeMap[i][j]->getNeighbors()->size(); k++) {
        std::cout << "Vecino i: " << this->_nodeMap[i][j]->getNeighbors()->get(k)->getPosI() << "\tj: " << this->_nodeMap[i][j]->getNeighbors()->get(k)->getPosJ() << std::endl;
    }*/
}

/**
 * Function that cleans the lists to reuse them later
 */
void PathfindingA::cleanLists() {

    this->_openSet->clear();
    this->_closeSet->clear();
    this->_path->clear();

}

/**
 * Function that calculates the best way to go from one position to another (if it exist)
 *
 * @param pMap - The map to check
 * @param pRows - The number of rows of the map
 * @param pColumns - The number of columns of the map
 * @param pStartI - The starting row number
 * @param pStartJ - The starting column number
 * @param pEndI - The ending row number
 * @param pEndJ - The ending column number
 * @return - The positions of the matrix/list to follow the best path
 */
PList<PList<int>> PathfindingA::getPath(int** pMap, int pRows, int pColumns, int pStartI, int pStartJ, int pEndI, int pEndJ) {

    this->initiateNodesMap(pMap, pRows, pColumns);

    Node* startNode = this->_nodeMap[pStartI][pStartJ];
    Node* endNode = this->_nodeMap[pEndI][pEndJ];

    //Inserts the starting node into the list of nodes for evaluating (openSet)
    this->_openSet->insert(startNode);

    //If there are nodes for evaluating
    while(this->_openSet->size() > 0) {

        int bestNodePosition = 0;

        //Looks for the best node in the list of nodes for evaluating (openSet)
        for(int i = 0; i < this->_openSet->size(); i++) {
            /*std::cout << " -> Nodo en Lista \ti: " << this->_openSet->get(i)->getPosI() << "\tj: " << this->_openSet->get(i)->getPosJ() <<
                      "\tCosto G: " << this->_openSet->get(i)->getCostG() << "\tCosto H: " << this->_openSet->get(i)->getCostH() <<
                      "\tCosto F: " << this->_openSet->get(i)->getCostF() << std::endl;*/

            if(this->_openSet->get(i)->getCostF() < this->_openSet->get(bestNodePosition)->getCostF())
                //Saves the position of the best node
                bestNodePosition = i;
        }

        //Our current node will be which was chosen as the best (the one with the lowest cost F)
        Node* currentNode = this->_openSet->get(bestNodePosition);

        /*std::cout << std::endl;
        std::cout << " * Nodo Ganador \ti: " << this->_openSet->get(bestNodePosition)->getPosI() << "\tj: " << this->_openSet->get(bestNodePosition)->getPosJ() <<
                  "\tCosto G: " << this->_openSet->get(bestNodePosition)->getCostG() << "\tCosto H: " << this->_openSet->get(bestNodePosition)->getCostH() <<
                  "\tCosto F: " << this->_openSet->get(bestNodePosition)->getCostF() << std::endl;
        std::cout << std::endl;*/

        //If the final node is reached (end of the path)
        if(currentNode == endNode){

            //Saves the current node in a temporary node
            Node* tempNode = currentNode;
            //Inserts the temporary node into the path list
            this->_path->insert(tempNode);

            //If the temporary node has a previous node
            while(tempNode->getPreviousNode()) {

                //Inserts the temporary node into the path list
                this->_path->insert(tempNode->getPreviousNode());
                //The temporary node will be the previous to the current
                tempNode = tempNode->getPreviousNode();
            }
            break;
        }

        //Removes the winning node (best node) in the list of nodes for evaluating
        this->_openSet->remove(bestNodePosition);

        //Inserts the winning node (best node) into the list of nodes already evaluated
        this->_closeSet->insert(currentNode);

        //Checks all the neighbors of the current node
        for(int i = 0; i < currentNode->getNeighbors()->size(); i++) {

            //If the current neighbor has not been evaluated and is not an obstacle (we can walk over it)
            if(!(this->inCloseSet(currentNode->getNeighbors()->get(i))) && !(currentNode->getNeighbors()->get(i)->getWalkable())) {

                //Estimates the G cost that the current neighbor will have
                int tmpCostG = currentNode->getCostG() + 1;

                //If the current neighbor is already in the list of nodes for evaluating (openSet)
                if (this->inOpenSet(currentNode->getNeighbors()->get(i))) {
                    //If the estimated G cost is better than that one it had
                    if (tmpCostG < currentNode->getNeighbors()->get(i)->getCostG())
                        //Defines the new G cost of the current neighbor
                        currentNode->getNeighbors()->get(i)->setCostG(tmpCostG);
                }
                else {
                    //Defines the G cost of the current neighbor
                    currentNode->getNeighbors()->get(i)->setCostG(tmpCostG);
                    //Inserts the current neighbor in the list of nodes for evaluating (openSet)
                    this->_openSet->insert(currentNode->getNeighbors()->get(i));
                }

                //Defines the H cost of the current neighbor
                currentNode->getNeighbors()->get(i)->setCostH(this->calculateHeuristics(currentNode->getNeighbors()->get(i), endNode));
                //Defines the F cost of the current neighbor
                currentNode->getNeighbors()->get(i)->setCostF((currentNode->getNeighbors()->get(i)->getCostG() +
                                                               currentNode->getNeighbors()->get(i)->getCostH()));
                //Defines the previous node of the current neighbor, who will be our current node
                currentNode->getNeighbors()->get(i)->setPreviousNode(currentNode);

                /*std::cout << "Nodo Vecino \ti: " << currentNode->getNeighbors()[i]->getPosI() << "\tj: "
                          << currentNode->getNeighbors()[i]->getPosJ() <<
                          "\tCosto G: " << currentNode->getNeighbors()[i]->getCostG() << "\tCosto H: "
                          << currentNode->getNeighbors()[i]->getCostH() <<
                          "\tCosto F: " << currentNode->getNeighbors()[i]->getCostF() << std::endl;*/
            }
        }
        //std::cout << std::endl;sa t
    }

    PList<PList<int>> positionPath;

    //If all nodes were evaluated and we never got to the goal
    if(this->_openSet->size() <= 0) {
        cout << "NO Solution Founded " << endl;
        this->cleanLists();
        return positionPath;
    }
    else {

        for(int i = ((int)this->_path->size() - 1); i >= 0; i--) {

            PList<int> positions;
            positions.insert(this->_path->get(i)->getPosI());
            positions.insert(this->_path->get(i)->getPosJ());
            positionPath.insert(positions);

        }

        cout << "Solution Founded" << endl;
        this->cleanLists();
        return positionPath;


    }

}
/*
    std::string stringPath = "";

    //If all nodes were evaluated and we never got to the goal
    if(this->_openSet->size() <= 0) {
        //std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "NO Solution Founded " << std::endl;
        this->cleanLists();
        return stringPath;
    }
    else {

        //int total = 0;

        for(int i = ((int)this->_path->size() - 1); i >= 0; i--) {
        stringPath += "[" + std::to_string(this->_path->get(i)->getPosI()) + "," + std::to_string(this->_path->get(i)->getPosJ()) + "] ";
        //total += this->_path[i]->getCostF();
    }
    //std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Solution Founded" - Total Cost: " << total << std::endl;
    this->cleanLists();
    return stringPath;*/

/*
    List<List<int>> positionPath;

    //If all nodes were evaluated and we never got to the goal
    if(this->_openSet->size() <= 0) {
        std::cout << "NO Solution Founded " << std::endl;
        this->cleanLists();
        return positionPath;
    }
    else {

    for(int i = ((int)this->_path->size() - 1); i >= 0; i--) {

        List<int> positions;
        positions.insert(this->_path->get(i)->getPosI());
        positions.insert(this->_path->get(i)->getPosJ());
        positionPath.insert(positions);

    }

        std::cout << "Solution Founded" << std::endl;
        this->cleanLists();
        return positionPath;*/
