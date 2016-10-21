CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o stack.o evaluation.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c $<

evaluation.o: evaluation.c evaluation.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *.o *~
	rm -f main
