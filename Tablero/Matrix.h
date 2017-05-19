#ifndef PRUEBAS_MATRIX_H
#define PRUEBAS_MATRIX_H

#include <iostream>
#include "List.h"

using  namespace std;

template<class t_data>

class Matrix{
private:
    List<List<t_data>*> *matrix;
    int width, height;
    void setMatrix();
public:
    Matrix(int height, int width);
    ~Matrix();
    void addAt(int row, int column,t_data data);
    t_data getData(int row, int column);
};

template<class t_data>
Matrix<t_data>::Matrix(int height, int width){
    matrix = new List<List<t_data>*>();
    this->width=width;
    this->height=height;
    setMatrix();
}

template<class t_data>
void Matrix<t_data>::setMatrix(){
    for (int i = 0; i < height; ++i) {
        List<t_data> *colum = new List<t_data>;
        colum->Add(width);
        matrix->Insert(colum);
    }
}

template<class t_data>
void Matrix<t_data>::addAt(int row, int column, t_data data){
    if(row<height & column<width & row>=0 & column>=0){
        matrix->Get(row)->addAt(data,column);
    }else{
        cout<<"This position does not exist"<<endl;
        exit(1);
    }
}

template<class t_data>
t_data Matrix<t_data>::getData(int row, int column) {
    if(row<height & column<width & row>=0 & column>=0){
        return matrix->Get(row)->Get(column);
    }else{
        cout<<"This position does not exist"<<endl;
        exit(1);
    }
}
#endif //PRUEBAS_MATRIX_H
