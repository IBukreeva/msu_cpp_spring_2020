CC=g++ -std=c++11

all: bigIntTest

bigIntTest: test.o bigint.o 
	$(CC) -o bigIntTest test.o bigint.o  
 
test: bigIntTest 
	./bigIntTest
	
test.o: test.cpp bigint.h  
	$(CC) -c test.cpp  
  
bigint.o: bigint.cpp bigint.h  
	$(CC) -c bigint.cpp 
  
clean:  
	rm -rf *.o bigIntTest
 
