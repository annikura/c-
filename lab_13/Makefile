CFLAGS = -Iinclude -Wall -Wextra -Werror -Wshadow -std=c++11
CC = g++
main.o = ./bin/main.o
main.cpp = ./src/main.cpp
my_array.h = ./include/my_array.h

main: bin $(main.o)
	$(CC) $(CFLAGS) $(main.o) -o main

$(main.o): $(main.cpp) $(my_array.h)
	$(CC) $(CFLAGS) -c $(main.cpp) -o $(main.o)
bin:
	mkdir bin
clean:
	rm -rf bin main