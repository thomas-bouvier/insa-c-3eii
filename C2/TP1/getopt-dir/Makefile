CC=gcc
CFLAGS=-Wall
LDFLAGS=

myecho: myecho.o
	$(CC) $(CFLAGS) $^ -o $@

myecho.o: myecho.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~
	rm -f myecho
