#include <iostream>
#include <cstring>
#include "parser.h"

onStrNum onStringCall = defaultOnStringFound;
onStrNum onNumberCall = defaultOnNumberFound;
onStartComplete onStartCall = defaultStartParsing;
onStartComplete onCompleteCall = defaultCompleteParsing;

void parse(const char * text){

    onStartCall(); //мне кажется, что даже если строка пустая,мы же ее рассматриваем и должны об этом сказать

    int i=0;
    while(i<strlen(text)){
        if(text[i]==' '){ i++; continue;}

        else if(text[i]>47 && text[i]<58){ //можно так отделять числа?
            char* num = new char[11];
            int j=i;
            while(j<strlen(text) && text[j]!=' '){
                num[j-i]=text[j];
                j++;
            }
            num[j-i]='\0';
            i=j;
            onNumberCall((const char*)num);
        }
        else{
            char* str = new char[11];
            int j=i;
            while(j<strlen(text) && text[j]!=' '){
                str[j-i]=text[j];
                j++;
            }
            str[j-i]='\0';
            i=j;
            onStringCall((const char*)str);
        }
    }

    onCompleteCall();
    return ;
}

void registerOnStringCallback(onStrNum callback){
    onStringCall=callback;
}
void registerOnNumberCallback(onStrNum callback){
    onNumberCall=callback;
}
void registerOnStartCallback(onStartComplete callback){
    onStartCall=callback;
}
void registerOnCompleteCallback(onStartComplete callback){
    onCompleteCall=callback;
}

void defaultStartParsing(void){
    std::cout <<"defaultStartParsing"<< std::endl;
}
void defaultCompleteParsing(void){
    std::cout <<"defaultCompleteParsing"<< std::endl;
}
void defaultOnNumberFound(const char *n){
    std::cout <<"defaultOnNumberFound:\n"<< n<< std::endl;
}
void defaultOnStringFound(const char *n){
    std::cout << "defaultOnStringFound:\n" << n<< std::endl;
}
