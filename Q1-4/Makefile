flags = -Wall -g -Werror

all: main

Euler.o: Euler.cpp Euler.hpp
	g++ $(flags) -c Euler.cpp

main.o: main.cpp Euler.hpp
	g++ $(flags) -c main.cpp

main: Euler.o main.o
	g++ $(flags) Euler.o main.o -o main

clean:
	rm -f *.o main