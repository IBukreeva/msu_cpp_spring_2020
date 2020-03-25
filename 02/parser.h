
void parse(const char * text);

using onString = void(*) (char* string);
using onNumber = void(*) (int number);
using onStartComplete = void(*) (void);

void registerOnStringCallback(onString callback);
void registerOnNumberCallback(onNumber callback); 
void registerOnStartCallback(onStartComplete callback);
void registerOnCompleteCallback(onStartComplete callback);

void defaultStartParsing(void);
void defaultCompleteParsing(void);
void defaultOnNumberFound(int n);
void defaultOnStringFound(char *n);
