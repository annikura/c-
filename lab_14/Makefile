CFLAGS = -Iinclude -Wall -Wextra -Wshadow -std=c++11
CC = g++

main.o = ./bin/main.o
matrix.o = ./bin/matrix.o

main.cpp = ./src/main.cpp
matrix.cpp = ./src/matrix.cpp

matrix.h = ./include/matrix.h

all: main

main: bin $(main.o) $(matrix.o)
	$(CC) $(CFLAGS) $(main.o) $(matrix.o) -o main

$(matrix.o): $(matrix.cpp) $(matrix.h) 
	$(CC) -c $(CFLAGS) $(matrix.cpp) -o $(matrix.o)

$(main.o): $(main.cpp) $(matrix.h)
	$(CC) -c $(CFLAGS) $(main.cpp) -o $(main.o)

bin:
	mkdir bin

clean:
	rm -rf bin main