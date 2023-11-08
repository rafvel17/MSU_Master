CC = g++ 

main: linearSystem.o
	$(CC) linearSystem.o Matrix.o -o main

linearSystem.o: linearSystem.cpp Matrix.h
	$(CC) -c linearSystem.cpp Matrix.cpp

Matrix.o: Matrix.cpp Matrix.h 
	$(CC) -c Matrix.cpp

run: 
	./main

clean:
	rm -rf *.o main
	rm -rf *.gch 