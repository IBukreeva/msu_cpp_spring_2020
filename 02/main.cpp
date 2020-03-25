#include <iostream>
#include "parser.h"

void onNumberFound1(int n){
    std::cout <<"onNumberFound1:\n"<< n<< std::endl;
}
void onNumberFound2(int n){
    std::cout << "onNumberFound2:\n" << n<< std::endl;
}

void onStringFound(char *n){
    std::cout << "onStringFound:\n" << n<< std::endl;
}

int main(){

    std::cout<< "\nTest1: <       >"<< std::endl;
    parse("        "); //колбэки начала и конца, но токенов не найдено

    registerOnNumberCallback(onNumberFound1);//теперь колбэк числа задан пользователем

    std::cout<< "\nTest2: <  testest 123 color flex>"<< std::endl;
    parse("  testest 123 color flex"); //коллбэки начала и конца, коллбэки токенов пользователя

    std::cout<< "\nTest3: <nodrama 4200 nocomedy>"<< std::endl;
    registerOnNumberCallback(onNumberFound2); 
    registerOnStringCallback(onStringFound);
    parse("nodrama 4200 nocomedy"); //еще раз изменили коллбэк для числа, в остальном все такое же

    return 0;
}
