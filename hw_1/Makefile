main.c = ./src/main.c
bmp.c = ./src/bmp.c

main.o = ./bin/main.o
bmp.o = ./bin/bmp.o

bmp.h = ./include/bmp.h

bin = $(./bin)

CC=gcc
CFLAGS =-g -I include -std=c99 -Wall -Wunknown-pragmas -Werror -Wshadow -Wextra

all: bin $(main.o) $(bmp.o)
	$(CC) $(main.o) $(bmp.o) -o main
bin: $(bin)
	mkdir bin
$(main.o): $(main.c)
	$(CC) $(CFLAGS) -c $(main.c) -o $(main.o)
$(bmp.o): $(bmp.c) $(bmp.h)
	$(CC) $(CFLAGS) -c $(bmp.c) -o $(bmp.o)
clean:
	rm -rf bin main
