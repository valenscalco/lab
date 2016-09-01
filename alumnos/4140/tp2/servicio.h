#ifndef _HIJO_H_
#define _HIJO_H_

int abrir_archivo(char *file_name);

void contar_palabras(char *line, int nchars, int fd_hijo_monitor[2]);

void lanzar_hijos(int cantidad, int fd_result[2]);

void calcular_resultado(int fd_monitor_padre[2], char *orden);

// int test(int saludo[2]);

#endif
