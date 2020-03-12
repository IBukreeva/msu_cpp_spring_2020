all: allocator 

allocator: main.o alloc.o 
	g++ -o allocator main.o alloc.o  
 
test: allocator  
	./allocator
	
main.o: main.cpp alloc.h  
	g++ -c main.cpp  
  
alloc.o: alloc.cpp alloc.h  
	g++ -c alloc.cpp  
  
clean:  
	rm -rf *.o allocator
