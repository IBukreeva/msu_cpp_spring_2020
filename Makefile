all: parser 

parser: main.o parser.o 
	g++ -o parser main.o parser.o  
 
test: parser  
	./parser
	
main.o: main.cpp parser.h  
	g++ -c main.cpp  
  
parser.o: parser.cpp parser.h  
	g++ -c parser.cpp 
  
clean:  
	rm -rf *.o parser
