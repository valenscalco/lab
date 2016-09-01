GETS= hacha
FLAGS= -Wall -g 
CC= gcc
TARGETS= hacha 

hacha: hacha.h main.c
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o *~
