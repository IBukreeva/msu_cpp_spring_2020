#include <iostream>
#include "matrix.h"


Matrix::Matrix(int size_row, int size_col) {
    size_rows = size_row;
    size_cols = size_col;

    rows = (Row**) malloc(size_rows*sizeof(Row));
    for(int i=0;i<size_rows;i++){
        rows[i] = new Row(size_cols);
    }

}

Matrix::~Matrix() {
    for(int i=0;i<size_rows;i++){
        free(rows[i]);
    }
    free(rows);
    size_cols=0;
    size_rows=0;
}


int Matrix::getRows() const{
    return size_rows;
}
     
int Matrix::getColumns() const{
    return size_cols;
}

void Matrix::operator *= (int x){
    
    for(int i=0;i<size_rows;i++){
        *rows[i] *= x;
    }

}

bool Matrix::operator ==(const Matrix& matr) const{
    if(size_rows!=matr.getRows()) return false;
    if(size_cols!=matr.getColumns()) return false;

    for(int i=0;i<size_rows;i++){
        if(rows[i]!=matr.rows[i]) return false;
    }
    return true;
}

bool Matrix::operator !=(Matrix& matr) const{ 
    if(size_rows!=matr.getRows()) return true;
    if(size_cols!=matr.getColumns()) return true;

    for(int i=0;i<size_rows;i++){
        if(*rows[i]!=*matr.rows[i]) return true;
    }
    return false;
}

Row& Matrix::operator[] (int n) const{
    if(n<0 || n>=size_rows) {
        throw std::out_of_range("");
    }

    return *rows[n];
}

void Matrix::operator =(Matrix& matr){

    size_rows = matr.getRows();
    size_cols = matr.getColumns();

    for(int i=0;i<size_rows;i++){
        *rows[i]=*matr.rows[i];
    }

}
