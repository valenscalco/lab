CC = gcc
CFLAGS = -g -Wall

TARGETS = web

all: $(TARGETS)

web: server.c service.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)


clean:
	rm -f $(TARGETS) *.o *~

