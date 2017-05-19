//
// Created by richard on 25/04/17.
//

#include "backtracking.h"

backtracking::backtracking() {
    salida.open("texto.txt",std::ios::out);
}
backtracking::~backtracking() {}

void backtracking::bactrack8Queens(int *locacion, int profundidad, int vuelta) {


    file = fopen("texto.txt","un");             //abre el fichero texto.txt para agregarle
//    fprintf(&file,"%d","hola");

   for(int ciclo = 0;ciclo < 8;ciclo++) {       //se guardan todas las posiciones del arreglo en el fichero

        if(locacion[ciclo]==-1){                //guarda un 8 si el valor es un -1
            salida<<" "<<8;

        }else{                                  //GUARDA el valor real
            salida<<" "<< locacion[ciclo];
        }
    }if(profundidad == 8){                      //guarda que encontro una solucion
        salida << " solucion";
    }
    salida<<std::endl;
    //fprintf(file, "%d","");

    if (profundidad ==-1){                      //se han encontrado ya todos los posibles movimientos de las reinas en el tablero termina el programa
        //finaliza el programa
        std::cout<<vuelta<<"\n";
        std::cout<<"fin del programa"<<"\n";


    }else if (profundidad==8){                  //SE encontro una posible solucion
        //tiene una solucion

        std::cout<<"solucion "<<locacion[0]<<","<<locacion[1]<<","<<locacion[2]<<","<<locacion[3]<<","
                 <<locacion[4]<<"," <<locacion[5]<<","<<locacion[6]<<"," <<locacion[7]<<"\n";
        locacion[profundidad-1] = locacion[profundidad-1]+1;                    // se le suma en uno al valor de la profundida anterior
        bactrack8Queens(locacion,profundidad-1,vuelta++);                       //se realiza recursividad regresandose en un lo posicion de la profundidad
    }else if(locacion[profundidad]==-1){
        locacion[profundidad] = 0;                                              //si locacion en la posicion profundidad  se le asigna un 0
        bactrack8Queens(locacion,profundidad,++vuelta);                         //aqui solo vuelve a llamar a la recursion
    }else if(locacion[profundidad] == 8){
        locacion[profundidad] = -1;
        locacion[profundidad-1] = locacion[profundidad-1]+1;
        bactrack8Queens(locacion, profundidad-1,++vuelta);
    }else {
        bool var = true;
        for (int i = 0; i < profundidad; i++) {
            if((locacion[i]== locacion[profundidad])||(abs(locacion[i]-locacion[profundidad])==abs(i-profundidad))){
                locacion[profundidad] = locacion[profundidad] +1;
                bactrack8Queens(locacion,profundidad,++vuelta);
                var = false;
                break;
            }
        }
        if(var){
            bactrack8Queens(locacion,profundidad+1,++vuelta);
        }

    }
}