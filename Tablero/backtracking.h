//
// Created by richard on 25/04/17.
//

#ifndef PRUEBAS_BACKTRACKING_H
#define PRUEBAS_BACKTRACKING_H

//#include <fstream>
//#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
class backtracking {
public:
    std::fstream salida;

    FILE *file;
    backtracking();
    ~backtracking();
    int location[8] = {-1,-1,-1,-1,-1,-1,-1,-1}; //crea un arreglo de 8 posiciones para almacenar las posibles soluciones del tablero
    void bactrack8Queens(int locacion[], int profundidad, int vuelta);
};


#endif //PRUEBAS_BACKTRACKING_H
