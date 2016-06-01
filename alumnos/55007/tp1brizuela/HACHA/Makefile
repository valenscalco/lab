GETS= cortar
FLAGS= -Wall -g 
CC= gcc
TARGETS= cortar 

cortar: cortar.h cortar.c
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o *~
