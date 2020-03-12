
#include <iostream>
#include "alloc.h"
size_t maxSize;
size_t pnt=0;
char * mem=nullptr;

void makeAllocator(size_t mSize){
    maxSize=mSize;
    mem = (char*) malloc(maxSize*sizeof(char));
    pnt = 0;
}

void reset(){
    pnt=0;
}

char * alloc(size_t size){
    if(mem==nullptr){ return nullptr;}
    if(pnt+size>maxSize){
        return nullptr;
    }
    char * ans = mem+pnt;
    pnt+=size;
    return ans;
}
