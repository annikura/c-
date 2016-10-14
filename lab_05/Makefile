main.c = ./src/main.c
clist.c = ./src/clist.c

main.o = ./bin/main.o
clist.o = ./bin/clist.o

clist.h = ./include/clist.h

main: bin $(main.o) $(clist.o)
	gcc $(main.o) $(clist.o) -o main
bin:
	mkdir bin
$(main.o): $(main.c) 
	gcc -c $(main.c) -o $(main.o)
$(clist.o): $(clist.h) $(clist.c)
	gcc -c $(clist.c) -o $(clist.o)
clean:
	rm -rf bin main
