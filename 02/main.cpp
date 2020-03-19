#include <iostream>
#include "parser.h"

void onNumberFound1(const char *n){
    std::cout <<"onNumberFound1:\n"<< n<< std::endl;
}

void onNumberFound2(const char *n){
    std::cout << "onNumberFound2:\n" << n<< std::endl;
}

void onStringFound(const char *n){
    std::cout << "onStringFound:\n" << n<< std::endl;
}

int main(){

    std::cout<< "\nTest1: <       >"<< std::endl;
    parse("        "); //колбэки начала и конца, но токенов не найдено

    registerOnNumberCallback(onNumberFound1);//теперь колбэк числа задан пользователем

    std::cout<< "\nTest2: <  testest 123 color flex>"<< std::endl;
    parse("  testest 123 color flex");

    std::cout<< "\nTest3: <nodrama 4200 nocomedy>"<< std::endl;
    registerOnNumberCallback(onNumberFound2); 
    registerOnStringCallback(onStringFound);
    parse("nodrama 4200 nocomedy"); //изменили коллбэк для числа и строк

    return 0;
}
