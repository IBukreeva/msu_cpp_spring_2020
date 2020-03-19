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
    parse("  testest 123 color flex"); //коллбэки начала и конца, коллбэки токенов пользователя

    std::cout<< "\nTest3: <nodrama 4200 nocomedy>"<< std::endl;
    registerOnNumberCallback(onNumberFound2); 
    registerOnStringCallback(onStringFound);
    parse("nodrama 4200 nocomedy"); //еще раз изменили коллбэк для числа, в остальном все такое же

    return 0;
}




//то есть он не сразу выводит эти штуки, а складывает в массив обработчиков и потом их выводит?
//если он вызывает парс то выводит я начал! колбэк
//потом идет по строке
//2 указателя на колбэки
//применит дейтсвие к строке которое указал пользователь
//к строке то же самое
//нам нужно в правильных местах вызывать обработчик
//далее в фотках схема описана
//проверяем на конкретных обработчиках
//на конкретных строках

//в библиотеке есть регистратор, 4 колбэка по умолчанию
//хранятся в массиве через указатели
//в мэйне можно что-нибудь попросить распарсить или сделать свой колбэк
//4 функции регистратора
//4 колбэка по умолчанию


//остальные 2 колбэка по умолчанию инициализированы и мы их не перерегистрируем