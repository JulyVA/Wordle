#ifndef JUGABLE_H
#define JUGABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define FILAS 6
#define COLUMNAS 5

#ifdef _WIN32
    #define limpiar "cls"
#else
    #define limpiar "clear"
#endif

typedef struct {
    char letra;
    char color;
} Letra;

void elegirColor(Letra** tablero, int filaActual, const char* objetivo);
void rellenar(Letra** tablero, int filaActual, const char* palabraSecreta);
void imprimirTablero(Letra** tablero, int filaActual, int columnaActual);
int comprobar(Letra** tablero, int filaActual);
int jugable(char *palabraSecreta);
char* obtenerSugerencia();
char* palabraRandom();

#endif