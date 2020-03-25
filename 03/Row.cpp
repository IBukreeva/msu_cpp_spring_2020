#include "Row.h"
#include <iostream>

Row::Row(int inSize){
    data = new int[inSize];
    size=inSize;
}
    
Row::~Row(){
    free(data);
    size=0;
}  

int Row::getSize() const {
    return size;
}

bool Row::operator!=(Row& r) const{
    if(size!=r.getSize()) return true;

    for(int i=0;i<size;i++){
        if(data[i]!=r.data[i]) return true;
    }

    return false;
}


bool Row::operator==(Row& r) const{
    if(size!=r.getSize()) return false;

    for(int i=0;i<size;i++){
        if(data[i]!=r.data[i]) return false;
    }

    return true;
}  

void Row::operator *= (int x){
    for(int i=0;i<size;i++){
        data[i]*=x;
    }
}

int& Row::operator [](int n) const {
    if(n<0 || n>=size){
        throw std::out_of_range("");
    }
    return data[n];
}

Row& Row::operator =(Row& r){
    this->~Row();

    size=r.getSize();
    data = new int[size];
    for(int i=0;i<size;i++){
        data[i]=r.data[i];
    }
    return *this;
 
}
