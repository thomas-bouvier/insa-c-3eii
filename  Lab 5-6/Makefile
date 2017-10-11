CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o list.o test.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

list.o: list.c list.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c test.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
