#include "ed2.h"

PalabraFrecuencia* palabras = NULL;
int totalPalabras = 0;

int contarPalabras(const char* archivo) {
    FILE* file = fopen(archivo, "r");

    int contador = 0;
    char palabra[6];
    while (fscanf(file, "%5[^,],%*d\n", palabra) == 1) {
        contador++;
    }

    fclose(file);
    return contador;
}

void cargarBaseDatos(const char* archivo) {
    totalPalabras = contarPalabras(archivo);

    palabras = (PalabraFrecuencia*)malloc(totalPalabras * sizeof(PalabraFrecuencia));

    FILE* file = fopen(archivo, "r");

    int index = 0;
    while (index < totalPalabras && fscanf(file, "%5[^,],%d\n", palabras[index].palabra, &palabras[index].frecuencia) == 2) {
        palabras[index].palabra[COLUMNAS] = '\0'; // Asegúrate de que la palabra termine en '\0'
        for (int i = 0; palabras[index].palabra[i] != '\0'; i++) {
            palabras[index].palabra[i] = toupper(palabras[index].palabra[i]);
        }
        index++;
    }

    fclose(file);
}

void liberarMemoria() {
    if (palabras) {
        free(palabras);
    }
}

void eliminarPalabra(const char* palabraEliminar) {
    for (int i = 0; i < totalPalabras; i++) {
        if (strcmp(palabras[i].palabra, palabraEliminar) == 0) {
            for (int j = i; j < totalPalabras - 1; j++) {
                palabras[j] = palabras[j + 1];
            }
            totalPalabras--;
            return;
        }
    }
}
