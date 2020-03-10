
all: main

main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c main.cpp

test: main
	./main
    
clean:
	rm -rf *.o main