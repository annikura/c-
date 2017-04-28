CFLAGS = -g -I include -std=c++11 -Werror -Wextra -Wshadow -Wall

my_vector.h = ./include/my_vector.h
main.cpp = ./src/main.cpp
main.o = ./bin/main.o

main: bin $(main.o)
	g++ $(main.o) -o main

$(main.o): $(main.cpp) $(my_vector.h)
	g++ -c $(main.cpp) -o $(main.o) $(CFLAGS)

bin: 
	mkdir bin

clean:
	rm -rf bin main
