CC=g++ -std=c++14

all: serializer 

serializer: test.o
	$(CC) -o serializer test.o
 
test: serializer 
	./serializer
	
test.o: test.cpp serializer.h  
	$(CC) -c test.cpp  
  
clean:  
	rm -rf *.o serializer 
