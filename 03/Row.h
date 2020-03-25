#ifndef ROW_H
#define ROW_H

class Row{
    friend class Matrix;
public:
    Row(int x);
    virtual ~Row();
    
    int getSize() const;
    bool operator ==(Row& row) const;
    void operator *= (int x);
    bool operator != (Row& r) const;
    Row& operator = (Row& r);
    int& operator [](int x) const;
    
    int * data; //мы же меняем строки, выходит, они паблик

private:
    int size;
    
};

#endif /* MATRIX */
