CC=gcc
CFLAGS=-g -Wall
LDLIBS=-lm

TARGETS=pegar hachar

all: $(TARGETS)

pegar: pegar.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

hachar: hachar.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

test-h: hachar
	./hachar -n 3 -f resources/dog.ppm

test-p: pegar
	ls resources/dog.ppm-* | ./pegar d.ppm

clean:
	rm -f $(TARGETS) *.o *~ resources/dog.ppm-* d.ppm

