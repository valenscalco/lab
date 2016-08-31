# Computación II: TP2: Comunicación entre procesos con pipes. 
# <federico.hernandez@um.edu.ar>
# <carlos.taffernaberry@um.edu.ar>

CC=gcc
CFLAGS=-g -Wall

tp2: tp2.o servicio.o
	$(CC) $(CFLAGS) -o $@ $^ 

test: tp2
	cat file.txt | ./tp2
	sleep 2

clean:
	$(RM) tp2 *.o *~

