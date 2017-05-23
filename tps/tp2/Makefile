CC=gcc
CFLAGS=-g -Wall
TARGETS=tp2

all: $(TARGETS)

tp2: tp2.c parser.c proc.c
	$(CC) $(CFLAGS) -o $@ $^

test: tp2
	cat noticia | ./tp2

format-text:
	fold -w 80 -s noticia > noticia2
	#fmt -w 80 noticia > noticia2

justify-text:
	par 80j < noticia2 > noticia
	rm -fv noticia2

clean:
	rm -f *~ .o $(TARGETS) noticia2


