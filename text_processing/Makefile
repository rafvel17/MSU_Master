CC = g++ $(CFLAGS)
CFLAGS = -O0 -g

vigenere_encode: vigenere_encode.cpp utf8/utf8.h utf8/utf8.cpp
	$(CC) -o vigenere_encode vigenere_encode.cpp utf8/utf8.cpp

clean:
	rm -f vigenere_encode vigenere_encode.o
