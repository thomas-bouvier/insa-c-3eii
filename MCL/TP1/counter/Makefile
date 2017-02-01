CC=gcc
CFLAGS=-Wall
LDFLAGS=-lcmocka

main: main.o counter.o
	$(CC) $^ $(LDFLAGS) -o $@

counter.o: counter.c counter.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
