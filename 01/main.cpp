#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "alloc.h"

int main(void){

    //до вызова makeAllocator память выделить нельзя, а после выделится
    {
        char *a0, *a1, *a2, *a3, *a4, *a5;

        //1
        a0 =alloc(100); //должно быть ничего
        
        makeAllocator(1000);

        a1 = alloc(100); //выделяется
        a4 = alloc(100); //выделяется
        if(a1!=nullptr && a0==nullptr && a4!=nullptr) std::cout<< "works1\n";

        reset();
        
        //2
        a1 = alloc(500); //выделяется
        a2 = alloc(600); //не выделяется
        if(a1!=nullptr && a2==nullptr) std::cout<< "works2\n";

        reset();

        //3
        a1 = alloc(1500); //не выделяется
        if(a1==nullptr) std::cout<< "works3\n";   

        reset();
        
        //4
        a1 = alloc(500); //выделяется
        reset(); 
        a5 = alloc(700); //выделяется
        if(a1!=nullptr && a5!=nullptr) std::cout<< "works4\n";
    }
    

    return 0;
}
