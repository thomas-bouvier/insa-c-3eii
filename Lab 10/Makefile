CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o edgeList_gcc64.o vertexList_gcc64.o graph_gcc64.o graph.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
