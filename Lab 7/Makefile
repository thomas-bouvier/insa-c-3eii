CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o myAlloc.o myFunctions.o test.o memoryList.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

myAlloc.o: myAlloc.c myAlloc.h
	$(CC) $(CFLAGS) -c $<

myFunctions.o: myFunctions.c myFunctions.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c test.h
	$(CC) $(CFLAGS) -c $<

memoryList.o: memoryList.c memoryList.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~
	rm -f main
