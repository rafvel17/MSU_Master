CC = g++ 

main: map_coords.o
	$(CC) map_coords.o R3Graph.o -o main

map_coords.o: map_coords.cpp R3Graph.h
	$(CC) -c map_coords.cpp R3Graph.cpp

R3Graph.o: R3Graph.cpp R3Graph.h 
	$(CC) -c R3Graph.cpp

run: 
	./main

clean:
	rm -rf *.o main
