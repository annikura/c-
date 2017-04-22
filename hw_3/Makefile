.PHONY: all clean 

CC = g++
CFLAGS = -std=c++11 -g -Isrc -Wall -Wextra -Wshadow -fsanitize=undefined -D_GLIBCXX_DEBUG

main.cpp = src/main.cpp
huffman.cpp = src/huffman.cpp
huffman.h = src/huffman.h

test.cpp = test_dir/test.cpp

test.o = bin/test.o
main.o = bin/main.o
huffman.o = bin/huffman.o

all: main test

main: bin $(main.o) $(huffman.o) 
	$(CC) $(CFLAGS) $(main.o) $(huffman.o) -o main

test: bin $(test.o) $(huffman.o)
	$(CC) $(CFLAGS) $(test.o) $(huffman.o) -o test -lgtest

$(test.o): $(test.cpp)
	$(CC) -c $(CFLAGS) $(test.cpp) -o $(test.o)

$(main.o): $(main.cpp) $(huffman.h) 
	$(CC) -c  $(main.cpp) -o $(main.o) $(CFLAGS)
	
$(huffman.o): $(huffman.cpp) $(huffman.h) 
	$(CC) -c  $(huffman.cpp) -o $(huffman.o) $(CFLAGS)

bin:
	mkdir bin

clean:
	rm -rf bin main


	