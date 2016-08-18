# Computación II: TP2: Comunicación entre procesos con pipes. 
# <federico.hernandez@um.edu.ar>
# <carlos.taffernaberry@um.edu.ar>

CC=gcc
#CFLAGS=-g -Wall -DDEBUG

tp2: tp2.c servicio.c monitor.c
	$(CC) $(CFLAGS) -o $@ $^ 

test: tp2
	cat file.txt | ./tp2

#cat new-file.txt | ./tp2

justify-text:
	# justify text at 80 characters
	par 80j < file.txt > new-file.txt

clean:
	$(RM) tp2 *.o *~

