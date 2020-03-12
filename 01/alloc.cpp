
#include <iostream>
#include "alloc.h"
size_t maxSize=1000;
size_t pnt=0;
char * mem=nullptr;

void makeAllocator(size_t maxSize){
    mem = (char*) malloc(maxSize*sizeof(char));
    pnt = 0;
    //printf("makeAllocator:: %p\n", mem);
}

void reset(){
    pnt=0;

}

char * alloc(size_t size){
    if(mem==nullptr){ return nullptr;}
    if(pnt+size>maxSize){
        //printf( "can't allocate memory");
        return nullptr;
    }
    char * ans = mem+pnt;
    pnt+=size;
    return ans;
}