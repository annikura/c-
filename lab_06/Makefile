main.c = ./src/main.c
main.o = ./bin/main.o

phonebook.c = ./src/phonebook.c
phonebook.o = ./bin/phonebook.o

phonebook.h = ./include/phonebook.h
names.h = ./include/names.h

bin = $(./bin)

main: bin $(main.o) $(phonebook.o)
	gcc $(main.o) $(phonebook.o) -o main -lexpat

bin: $(bin)
	mkdir bin

$(phonebook.o): $(phonebook.c) $(phonebook.h) $(names.h)
	gcc -c $(phonebook.c) -o $(phonebook.o)

$(main.o): $(main.c)
	gcc -c $(main.c) -o $(main.o)

clean:
	rm -rf bin main
