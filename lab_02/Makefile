str.o = ./bin/str.o
tests_str.o = ./bin/tests_str.o
test.o = ./bin/test.o

str.h = ./include/str.h
tests_str.h = ./include/tests_str.h

str.c = ./src/str.c
test.c = ./src/test.c
tests_str.c = ./src/tests_str.c

test = ./bin/test

$(str.o): bin $(str.c) $(str.h)
	gcc -c $(str.c) -o $(str.o)
test: bin $(str.o) $(tests_str.o) $(test.o) $(test)
	gcc $(test.o) $(str.o) $(tests.str.o) -o $(test)
$(tests_str.o): bin $(str.o) $(tests_str.c) $(tests_str.h)
	gcc -c  $(tests_str.c) -o $(tests_str.o)
$(test.o): bin $(test.c) $(tests_str.o)
	gcc -c $(test.c) -o $(test.o)
bin: 
	mkdir bin
clean:
	rm -rf bin
