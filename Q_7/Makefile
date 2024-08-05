
all: race

race: race.c
	gcc -g -o race race.c -lpthread

valgrind_helgrind: race
	valgrind --tool=helgrind ./race

clean:
	rm -f race race.o