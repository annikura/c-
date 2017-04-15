CC = g++
CFLAGS = -std=c++11 -g -Wall -Wextra -Werror -Wshadow -fsanitize=undefined -D_GLIBCXX_DEBUG

main.cpp = src/main.cpp
huffman.cpp = src/huffman.cpp
huffman.h = src/huffman.h

main.o = bin/main.o
huffman.o = bin/huffman.o

all: main

main: bin $(main.o) $(huffman.o) 
	$(CC) $(CFLAGS) $(main.o) $(huffman.o) -o main

$(main.o): $(main.cpp) $(huffman.h) 
	$(CC) -c  $(main.cpp) -o $(main.o) $(CFLAGS)
	
$(huffman.o): $(huffman.cpp) $(huffman.h) 
	$(CC) -c  $(huffman.cpp) -o $(huffman.o) $(CFLAGS)

bin:
	mkdir bin

clean:
	rm -rf bin main
