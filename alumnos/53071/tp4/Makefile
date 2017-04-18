CC = gcc 
CFLAGS= -g -Wall
TARGETS = tp4
all: $(TARGETS)

tp4: server6.c http.c uri.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o  


