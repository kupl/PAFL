CC:=gcc
CFLAGS:=
LDFLAGS:=

all: test

test: test1.o example.o
	$(CC) $(CFLAGS) $(LDFLAGS) test1.o example.o -o test

example.o: example.c
	$(CC) $(CFLAGS) -o example.o -c example.c 

test1.o: test1.c
	$(CC) $(CFLAGS) -o test1.o -c test1.c

clean:
	rm -f *.gcov
	rm -f *.gcda *.gcno
	rm -f *.o
	rm -f test
