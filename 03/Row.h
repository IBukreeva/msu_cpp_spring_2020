#include <iostream>
#ifndef ROW_H
#define ROW_H

class Row{
    friend class Matrix;
public:
    Row(): size(0) { };
    Row(size_t x);
    ~Row();
    
    size_t getSize() const;
    bool operator ==(Row& row) const;
    Row& operator *= (int x);
    bool operator != (Row& r) const;
    Row& operator = (Row& r);
    int& operator [](size_t x) const;

private:
    int * data;
    size_t size;
    
    void init(size_t x);
};

#endif /* ROW_H */
