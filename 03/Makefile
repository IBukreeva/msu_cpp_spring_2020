all: matrix 

matrix: main.o matrix.o Row.o
	g++ -o matrix main.o matrix.o Row.o
 
test: matrix  
	./matrix
	  
main.o: main.cpp matrix.h 
	g++ -c main.cpp  
  
matrix.o: matrix.cpp matrix.h  
	g++ -c matrix.cpp 
  
Row.o: Row.cpp Row.h  
	g++ -c Row.cpp   

clean:  
	rm -rf *.o matrix
	
	
