#include <iostream>
#include <cstring>
#include "parser.h"

onString onStringCall = defaultOnStringFound;
onNumber onNumberCall = defaultOnNumberFound;
onStartComplete onStartCall = defaultStartParsing;
onStartComplete onCompleteCall = defaultCompleteParsing;

void parse(const char * text){

    onStartCall(); //мне кажется, что даже если строка пустая, мы же ее рассматриваем и должны об этом сказать

    int i=0;
    int len_text=strlen(text);
    while(i<len_text){
        if(text[i]==' '){ i++; continue;}

        else if(text[i]>='0' && text[i]<='9'){
            int number = 0; 
            int j=i;
            while(j<len_text && text[j]!=' '){
                number = number*10 + text[j]-'0'; //получается, что диапазон ограничен int
                j++;
            }
            i=j;
            onNumberCall(number);
        }
        else{
            char* str = (char*)malloc((len_text-i)*sizeof(char)); 
            int j=i;
            while(j<len_text && text[j]!=' '){
                str[j-i]=text[j];
                j++;
            }
            str[j-i]='\0';
            i=j;
            onStringCall(str);
            free (str);
        }
    }

    onCompleteCall();
    return ;
}

void registerOnStringCallback(onString callback){
    onStringCall=callback;
}
void registerOnNumberCallback(onNumber callback){
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
void defaultOnNumberFound(const int n){
    std::cout <<"defaultOnNumberFound:\n"<< n<< std::endl;
}
void defaultOnStringFound(const char *n){
    std::cout << "defaultOnStringFound:\n" << n<< std::endl;
}
