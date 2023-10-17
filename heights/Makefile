CC = g++ 

main: triangle_heights.o
	$(CC) triangle_heights.o R2Graph.o -o main

triangle_heights.o: triangle_heights.cpp R2Graph.h 
	$(CC) -c triangle_heights.cpp 
R2Graph.o: R2Graph.cpp R2Graph.h 
	$(CC) -c R2Graph.cpp
run: 
	./main

clean:
	rm -rf *.o main