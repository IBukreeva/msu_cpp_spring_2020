#pragma once
void parse(const char * text);

using onString = void(*) (const char* string);
using onNumber = void(*) (const int number);
using onStartComplete = void(*) (void);

void registerOnStringCallback(onString callback);
void registerOnNumberCallback(onNumber callback); 
void registerOnStartCallback(onStartComplete callback);
void registerOnCompleteCallback(onStartComplete callback);

void defaultStartParsing(void);
void defaultCompleteParsing(void);
void defaultOnNumberFound(const int n);
void defaultOnStringFound(const char *n);
