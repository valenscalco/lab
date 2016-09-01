GETS=histograma
FLAGS= -Wall -g 
CC= gcc
TARGETS= histograma

histograma: histograma.h main.c parametros.c master.c contador.c romper.c
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o *~
