#include <cstdio>
#include <cstdlib>
#include <iostream>

char * mem;
size_t pnt;
size_t maxSize=1000;

using namespace std;
void makeAllocator(size_t maxSize);
char* alloc(size_t size);
void reset();

int main(void){


    //test1 - просто тест
    //в a0 должно быть ничего, для a1 и a4 память выделилась 
    {
        char * a0 =alloc(100); //должно быть ничего
        makeAllocator(maxSize);

        char * a1 = alloc(100);
        char * a4 = alloc(100);

        if(a1!=nullptr && a0==nullptr && a4!=nullptr) std::cout<< "works1\n";
    }
    delete mem; mem=nullptr;

    //test2 - постепенно просим больше, чем есть
    //то есть 1й раз память выделится, а 2й раз должно быть nullptr
    {
        makeAllocator(maxSize);

        char * a1 = alloc(500);
        char * a2 = alloc(600);
        if(a1!=nullptr && a2==nullptr) std::cout<< "works2\n";
    }
    delete mem; mem=nullptr;

    //test3 - сразу просим больше, чем есть
    //то есть ничего не выделится
    {
        makeAllocator(maxSize);

        char * a1 = alloc(1500);
        if(a1==nullptr) std::cout<< "works3\n";    
    }
     delete mem; mem=nullptr;



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
    delete mem; mem=nullptr;



    return 0;
}


void makeAllocator(size_t maxSize){
    mem = (char*) malloc(maxSize*sizeof(char));
    pnt = 0;
}


void reset(){
    pnt=0;

}

char * alloc(size_t size){
    if(mem==nullptr){ return nullptr;}
    if(pnt+size>maxSize) {
        //printf( "can't allocate memory");
        return nullptr;
    }
    char * ans = mem+pnt;
    pnt+=size;
    return ans;
}
