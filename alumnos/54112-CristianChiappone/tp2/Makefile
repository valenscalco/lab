CC=gcc
CFLAGS=-g -Wall
TARGETS=tp2

all: $(TARGETS)

format:
	fold -w 80 -s noticia > noticia

clean:
	rm -f *~ .o $(TARGETS) 


tp2:  main.c c_cat.c c_getopt.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o*~
