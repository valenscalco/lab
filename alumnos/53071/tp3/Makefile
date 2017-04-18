CC=gcc
CFLAGS= -g -Wall
LDLIBS= -pthread
TARGETS=tp3

all: $(TARGETS)

tp3: main.c contador.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

test: main
	cat file.txt | ./main
	./main -i file.txt

clean:
		rm -f $(TARGETS) *~ core*


	

