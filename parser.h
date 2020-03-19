
void parse(const char * text);

using onStrNum = void(*) (const char* string);
using onStartComplete = void(*) (void);

void registerOnStringCallback(onStrNum callback);
void registerOnNumberCallback(onStrNum callback); 
void registerOnStartCallback(onStartComplete callback);
void registerOnCompleteCallback(onStartComplete callback);

void defaultStartParsing(void);
void defaultCompleteParsing(void);
void defaultOnNumberFound(const char *n); //может быть тут надо было сделать число?
void defaultOnStringFound(const char *n);