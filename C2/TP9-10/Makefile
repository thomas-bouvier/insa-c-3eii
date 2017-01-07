CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o binary_tree.o list.o huffman.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

binary_tree.o: binary_tree.c binary_tree.h
	$(CC) $(CFLAGS) -c $<

list.o: list.c list.h
	$(CC) $(CFLAGS) -c $<

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
