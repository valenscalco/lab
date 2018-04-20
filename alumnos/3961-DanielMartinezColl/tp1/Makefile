TARGET = tp1
CC:=gcc
CFLAGS = -g -Wall

tp1 : tp1.c 
	$(CC) -o $@ $^ $(CFLAGS)

test:
	cat noticia1 | ./tp1

clean:
	rm tp1
