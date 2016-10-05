ms_cli.c = ./src/ms_cli.c
mergesort.c = ./src/mergesort.c

mergesort.h = ./include/mergesort.h

mergesort.o = ./bin/mergesort.o
ms_cli.o = ./bin/ms_cli.o

all: bin $(ms_cli.o) $(mergesort.o)
	gcc $(ms_cli.o) $(mergesort.o) -o ms_cli
$(ms_cli.o): $(ms_cli.c)
	gcc -c $(ms_cli.c) -o $(ms_cli.o)
$(mergesort.o): $(mergesort.c) $(mergesort.h)
	gcc -c $(mergesort.c) -o $(mergesort.o)
bin:
	mkdir bin
clean: 
	rm -rf bin ms_cli
