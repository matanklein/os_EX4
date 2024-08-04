
all: hello

hello: hello.o
	gcc -g -o hello hello.c

valgrind_memcheck: hello
	valgrind --leak-check=full ./hello

valgrind_debuger: hello
	valgrind --vgdb=yes --vgdb-error=0 ./hello

clean:
	rm -f hello hello.o