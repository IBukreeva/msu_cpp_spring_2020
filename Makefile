CC=g++ -std=c++14

all: sort

sort: test.o sort.o 
	$(CC) -o sort test.o sort.o 
 
test: sort
	./sort
	
test.o: test.cpp sort.h
	$(CC) -c test.cpp
  
sort.o: sort.cpp sort.h
	$(CC) -c sort.cpp

clean:  
	rm -rf *.o sort