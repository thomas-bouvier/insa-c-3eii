CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o image.o fichier.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

image.o: image.c image.h
	$(CC) $(CFLAGS) -c $<

fichier.o: fichier.c fichier.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
