io.o = ./bin/io.o
algorithm.o = ./bin/algorithm.o
main.o = ./bin/main.o
util.o = ./bin/util.o

algorithm.c = ./src/algorithm.c
io.c = ./src/io.c
util.c = ./src/util.c
main.c = ./src/main.c

io.h = ./include/io.h
util.h = ./include/util.h
algorithm.h = ./include/algorithm.h

lab1: bin $(io.o) $(algorithm.o) $(main.o) $(util.o)
	gcc $(algorithm.o) $(io.o) $(main.o) $(util.o) -o lab1
bin:
	mkdir bin
$(algorithm.o): $(algorithm.c) $(algorithm.h)
	gcc -c $(algorithm.c) -o $(algorithm.o)
$(io.o): $(io.c) $(io.h)
	gcc -c $(io.c) -o $(io.o)
$(util.o): $(util.c) $(util.h)
	gcc -c $(util.c) -o $(util.o)
$(main.o): $(main.c) $(main.h)
	gcc -c $(main.c) -o $(main.o)
clean:
	rm -rf bin lab1 

