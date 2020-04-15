CC=g++ -std=c++14

all: formatCheck

formatCheck: test.o 
	$(CC) -o formatCheck test.o 
 
test: formatCheck
	./formatCheck
	
test.o: test.cpp format.h  
	$(CC) -c test.cpp  
  
clean:  
	rm -rf *.o formatCheck