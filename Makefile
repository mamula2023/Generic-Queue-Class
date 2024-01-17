CC=gcc
CFLAGS=-I.
DEPS = queue.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o queue.o
	$(CC) -o main main.o queue.o
