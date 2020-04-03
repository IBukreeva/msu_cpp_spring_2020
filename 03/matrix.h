#include "Row.h"
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    friend class Row;
public:
    Matrix(size_t row, size_t col);
    ~Matrix();
    size_t getRows() const;
    size_t getColumns() const;

    Row& operator[] (size_t x) const;
    Matrix& operator*= (int x);
    bool operator== (const Matrix&) const;
    bool operator!= (const Matrix&) const;
    void operator = (const Matrix&);
    
private:
    Row * rows;
    size_t size_rows;
    size_t size_cols;
};

#endif /* MATRIX */
