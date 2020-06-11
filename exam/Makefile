CC=g++ -std=c++11

all: test

summator: test.o summator.o 
	$(CC) -o summator test.o summator.o 
 
test: summator
	./summator
	
test.o: test.cpp summator.h
	$(CC) -c test.cpp
  
summator.o: summator.cpp summator.h
	$(CC) -c summator.cpp

clean:  
	rm -rf *.o summator
