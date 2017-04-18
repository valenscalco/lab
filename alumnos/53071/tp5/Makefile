CC = gcc 
CFLAGS= -g -Wall
TARGETS = tp5
all: $(TARGETS)

tp5: prueba.c http_h.c uri_h.c mime.c create_sock.c
	$(CC) $(CFLAGS) -o $@ $^ -pthread

clean:
	rm -fv $(TARGETS) *.o  
