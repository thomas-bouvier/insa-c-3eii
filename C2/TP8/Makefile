CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o myDoubleTree.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

myAlloc.o: myDoubleTree.c myDoubleTree.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
