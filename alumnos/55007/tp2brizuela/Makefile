GETS= histograma
FLAGS= -Wall -g
CC= gcc
TARGETS= histograma

histograma: histograma.h main.c parametros.c romper.c distrib.c ordenamiento.c
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -fv $(TARGETS) *.o*~
