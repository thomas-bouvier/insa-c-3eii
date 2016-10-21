CC=gcc
CFLAGS=-Wall
LDFLAGS=

main: main.o stack.o evaluation.o evaluationFromString.o
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c $<

evaluation.o: evaluation.c evaluation.h
	$(CC) $(CFLAGS) -c $<

evaluationFromString.o: evaluationFromString.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~
	rm -f main
