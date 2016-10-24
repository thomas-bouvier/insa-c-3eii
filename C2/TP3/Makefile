CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o fichier_gcc64.o image.o
		$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
		$(CC) $(CFLAGS) -c $<

image.o: image.c image.h
		$(CC) $(CFLAGS) -c $<

clean:
		rm -f *~
		rm -f main
