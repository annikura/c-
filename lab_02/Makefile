str.o = ./bin/str.o
test_str.o = ./bin/test_str.o
test.o = ./bin/test.o

str.h = ./include/str.h
test_str.h = ./include/test_str.h

str.c = ./src/str.c
test.c = ./src/test.c
test_str.c = ./src/test_str.c

test = ./bin/test

$(str.o): bin $(str.c) $(str.h)
	gcc -c $(str.c) -o $(str.o)
$(test): $(str.o) $(test_str.o) $(test.o)
	gcc $(test.o) $(str.o) $(test_str.o) -o $(test)
$(test_str.o): bin $(test_str.c) $(test_str.h)
	gcc -c  $(test_str.c) -o $(test_str.o)
$(test.o): bin $(test.c)
	gcc -c $(test.c) -o $(test.o)
bin: 
	mkdir bin
clean:
	rm -rf bin
