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
