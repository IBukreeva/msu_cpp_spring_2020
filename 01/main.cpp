#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "alloc.h"

using namespace std;
extern char * mem;
extern size_t maxSize;
extern size_t pnt;

int main(void){

    //test1 - просто тест
    //до вызова makeAllocator память выделить нельзя, а после выделится
    {
        char * a0 =alloc(100); //должно быть ничего
        makeAllocator(1000);

        char * a1 = alloc(100);
        char * a4 = alloc(100);
        
        if(a1!=nullptr && a0==nullptr && a4!=nullptr) std::cout<< "works1\n";
    }
    delete[] mem; mem=nullptr;

    //test2 - постепенно просим больше, чем есть
    //то есть 1й раз память выделится, а 2й раз должно быть nullptr
    {
        makeAllocator(1000);

        char * a1 = alloc(500);
        char * a2 = alloc(600);
        if(a1!=nullptr && a2==nullptr) std::cout<< "works2\n";
    }
    delete [] mem; mem=nullptr;

    //test3 - сразу просим больше, чем есть
    //то есть ничего не выделится
    {
        makeAllocator(1000);

        char * a1 = alloc(1500);
        if(a1==nullptr) std::cout<< "works3\n";    
    }
    delete[] mem; mem=nullptr;



    //test4 - просим до reset() меньше maxSize, после тоже меньше
    // а в сумме больше maxSize
    //то есть оба указателя существуют
    {
        makeAllocator(maxSize);

        char * a1 = alloc(500);
        reset();
        char * a5 = alloc(700);
        if(a1!=nullptr && a5!=nullptr) std::cout<< "works4\n";
    }
    delete[] mem; mem=nullptr;



    return 0;
}
