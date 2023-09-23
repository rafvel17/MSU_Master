CC = g++ 

main: triangle_heights.o
	$(CC) triangle_heights.o -o main

triangle_heights.o: triangle_heights.cpp R2Graph.cpp 
	$(CC) -c triangle_heights.cpp R2Graph.cpp

run: 
	./main

clean:
	rm -rf *.o main