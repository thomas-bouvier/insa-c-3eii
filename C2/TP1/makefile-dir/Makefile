CC=gcc					# Program for compiling C programs
CFLAGS=-Wall		# Extra flags to give to the C compiler
LDFLAGS=				# Extra flags to give to the linker

myhello: myhello.o mytools.o
	$(CC) myhello.o mytools.o -o myhello

# myhello.o: myhello.c mytools.h \
	$(CC) $(CFLAGS) -c $< -o $@

# mytools.o: mytools.c mytools.h \
	$(CC) $(CFLAGS) -c $< -o $@

myhello.o: mytools.h
mytools.o: mytools.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~
	rm -f myhello
