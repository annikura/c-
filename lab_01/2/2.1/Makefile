lab1: io.o algorithm.o main.o util.o
	gcc algorithm.o io.o main.o util.o -o lab1
algorithm.o: algorithm.c
	gcc -c algorithm.c -o algorithm.o
io.o: io.c
	gcc -c io.c -o io.o
util.o: util.c
	gcc -c util.c -o util.o
main.o: main.c
	gcc -c main.c -o main.o
clean:
	rm *.o lab1 

