CC = gcc
OBJECTS = pegar.o guardar.o
CFLAGS = -c $(DEBUG)

tp1 : $(OBJECTS)
		$(CC) $(DEBUG) $(OBJECTS) -o tp1
		@echo "Ejecutable creado exitosamente"
pegar.o : pegar.c guardar.c head.h
		$(CC) $(CFLAGS) pegar.c
guardar.o : guardar.c head.h
		$(CC) $(CFLAGS) guardar.c

