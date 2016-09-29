main.c = ./src/main.c
clist.c = ./src/clist.c

main.o = ./bin/main.o
clist.o = ./bin/clist.o

clist.h = ./include/clist.h

pose_db = ./bin/pose_db

$(pose_db): bin $(clist.o) $(main.o)
	gcc $(main.o) $(clist.o) -o $(pose_db)
bin: 
	mkdir ./bin
$(main.o): $(main.c)
	gcc -c $(main.c) -o $(main.o)
$(clist.o): $(clist.c) $(clist.h)
	gcc -c $(clist.c) -o $(clist.o)
clean:
	rm -rf bin

