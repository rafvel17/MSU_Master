CC = g++ $(CFALGS)
CFLAGS = -O0 -g

earthdist: earthdist.cpp R3Graph.h R3Graph.cpp
	$(CC) -o earthdist earthdist.cpp R3Graph.cpp

clean:
	rm -f earthdist earthdist.exe
