CC=g++ -std=c++14

all: ThreadPool

ThreadPool: test.o 
	$(CC) -o ThreadPool test.o 
 
test: ThreadPool
	./ThreadPool
	
test.o: test.cpp threadPool.h
	$(CC) -c test.cpp
  
clean:  
	rm -rf *.o ThreadPool
