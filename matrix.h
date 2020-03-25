//Нужно написать класс-матрицу, тип элементов int. 
//В конструкторе задается количество рядов и строк. 

//+получить количество строк(rows)/
//+столбцов(columns), 

// получить конкретный элемент, - по скобочкам и приравнять.......7 как это сделать?

// умножить на число(*=), 
// сравнение на равенство/
// неравенство. 
// В случае ошибки выхода за границы бросать исключение: throw std::out_of_range("")


//написать конструктор и деструктор нормальные
//как работают исключчения?
#include "Row.h"

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    friend class Row;
public:
    Matrix(int row, int col);
    virtual ~Matrix();
    int getRows() const;
    int getColumns() const;

    Row& operator[] (int x) const;
    void operator*= (int x);
    bool operator ==(const Matrix&) const;
    bool operator !=(Matrix&) const;
    void operator =(Matrix&);
    Row ** rows;

private:
    int size_rows;
    int size_cols;
    
};

#endif /* MATRIX */