#include <iostream>
#include "matrix.h"

Matrix::Matrix(size_t row_size, size_t col_size) {
    size_rows = row_size;
    size_cols = col_size;

    rows = new Row[size_rows];
    for(size_t i=0; i<size_rows;i++){
        rows[i].init(size_cols);
    }
}

Matrix::~Matrix() {
    delete[] rows;
    size_cols=0;
    size_rows=0;
}

size_t Matrix::getRows() const{
    return size_rows;
}

size_t Matrix::getColumns() const{
    return size_cols;
}

Matrix& Matrix::operator *= (int x){

    for(size_t i=0;i<size_rows;i++){
        rows[i] *=x;
    }
    return *this;
}

bool Matrix::operator ==(const Matrix& matr) const{

    if(size_rows!=matr.getRows()) return false;
    if(size_cols!=matr.getColumns()) return false;

    for(size_t i=0;i<size_rows;i++){
        if(rows[i]!=matr.rows[i]) return false;
    }
    return true;
}

bool Matrix::operator !=(const Matrix& matr) const{ 
    return !(*this==matr);
}

Row& Matrix::operator[] (size_t n) const{
    if(n>=size_rows) {
        throw std::out_of_range("");
    }
    return rows[n];
}

void Matrix::operator =(const Matrix& matr){

    size_rows = matr.getRows();
    size_cols = matr.getColumns();

    for(size_t i=0;i<size_rows;i++){
        rows[i]=matr.rows[i];
    }
}
