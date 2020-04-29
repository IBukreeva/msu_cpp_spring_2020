CC=g++ -std=c++14

all: Vector

Vector: test.o 
	$(CC) -o Vector test.o 
 
test: Vector
	./Vector
	
test.o: test.cpp vector.h allocator.h iterator.h
	$(CC) -c test.cpp
  
clean:  
	rm -rf *.o Vector
