CC = g++ 

main: map_coords.o
	$(CC) map_coords.o -o main

map_coords.o: map_coords.cpp R3Graph.cpp 
	$(CC) -c map_coords.cpp R3Graph.cpp

run: 
	./main

clean:
	rm -rf *.o main
