CFLAGS=-O2 -g -Wall -Wextra

dsalloc: dsalloc.o
	ar rc libdsalloc.a dsalloc.o

example: example.c dsalloc.o
	cc $(CFLAGS) dsalloc.o example.c -o example

dsalloc.o: dsalloc.c dsalloc.h
	cc $(CFLAGS) -c dsalloc.c

# Install in debian local lib / include folders
install:
	@sudo cp libdsalloc.a /usr/local/lib && echo "libdsalloc.a installed at /usr/local/lib"
	@sudo cp dsalloc.h /usr/local/include && echo "dsalloc.h installed at /usr/local/include"

clean:
	rm -f *.o
	rm -f example

