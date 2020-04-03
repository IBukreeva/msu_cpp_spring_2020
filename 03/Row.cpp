#include <iostream>
#include "Row.h"

Row::Row(size_t inSize){
    this->init(inSize);
}

void Row::init(size_t inSize){
    data = new int[inSize];
    size=inSize;
}

Row::~Row(){
    delete[] data;
    size=0;
}

size_t Row::getSize() const {
    return size;
}

bool Row::operator==(const Row& r) const{
    if(size!=r.getSize()) return false;

    for(size_t i=0;i<size;i++){
        if(data[i]!=r.data[i]) return false;
    }
    return true;
}

bool Row::operator!=(const Row& r) const{
    return !(*this==r);
}

Row& Row::operator *= (int x){
    for(size_t i=0;i<size;i++){
        data[i]*=x;
    }
    return *this;
}

int& Row::operator [](size_t n) const {
    if(n>=size){
        throw std::out_of_range("");
    }
    return data[n];
}

Row& Row::operator =(const Row& r){
    
    if(this==&r)
        return *this;
    
    size = r.getSize();
    int * tmp = new int[size];
    delete[] data;
    data = tmp;
    for(size_t i=0;i<size;i++){
        data[i]=r.data[i];
    }
    return *this;

}
