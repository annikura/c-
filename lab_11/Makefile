CFLAGS = -g -I include -std=c++98 -Wall -Wunknown-pragmas -Werror -Wshadow -Wextra

main.cpp = ./src/main.cpp
employees.cpp = ./src/employees.cpp


main.o = ./bin/main.o
employees.o = ./bin/employees.o

employees.h = ./include/employees.h

empl_db: bin $(main.o) $(employees.o)
	g++ $(main.o) $(employees.o) -o empl_db

bin:
	mkdir bin

$(main.o): $(main.cpp) $(employees.h)
	g++ $(CFLAGS) -c $(main.cpp) -o $(main.o)

$(employees.o): $(employees.cpp) $(employees.h)
	g++ $(CFLAGS) -c $(employees.cpp) -o $(employees.o)

clean:
	rm -rf bin empl_db
