CC=gcc
CFLAGS=-g -Wall
TARGETS=e1 e2

all: $(TARGETS)

e1: e1.c lib.c
	$(CC) $(CFLAGS) -o $@ $^

e2: e2.c lib.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS) *~

