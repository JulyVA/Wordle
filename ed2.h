#ifndef ED2_H
#define ED2_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jugable.h"

typedef struct {
    char palabra[COLUMNAS + 1];
    int frecuencia;
} PalabraFrecuencia;

extern PalabraFrecuencia* palabras;
extern int totalPalabras;

int contarPalabras(const char* archivo);
void cargarBaseDatos(const char* archivo);
void liberarMemoria();
void eliminarPalabra(const char* palabraEliminar);

#endif