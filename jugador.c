#include "jugador.h"
#include "jugable.h"
#include "ed2.h"

char grises[27];
int cgrises = 0;

char* obtenerSugerencia(Letra** tablero, int filaActual) {
    char* sugerencia = NULL;
    int mejorFrecuencia = -1;
    int conteoVerdes[26] = {0};
    int eliminarIndices[totalPalabras];
    int eliminarCount = 0;
    char ingresada[COLUMNAS+1];
    
    //guarda las verdes y cuenta cuantas veces se repiten, y registra la palabra ingresada para luego eliminarla de posibles sugerencias
    for (int i = 0; i < COLUMNAS; i++) {
        if (tablero[filaActual][i].color == 'V') {
            conteoVerdes[tablero[filaActual][i].letra - 'A']++;
        }
        ingresada[i]=tablero[filaActual][i].letra;
    }
    ingresada[COLUMNAS]='\0';
    eliminarPalabra(ingresada);

    //guarda las grises y cuenta cuantas hay
    for (int i = 0; i < COLUMNAS; i++) {
        char letra = tablero[filaActual][i].letra;
        char color = tablero[filaActual][i].color;
        if (color == 'G' && conteoVerdes[letra - 'A'] == 0) {
            if (strchr(grises, letra) == NULL) {
                grises[cgrises++] = letra;
            }
        }
    }

    //si hay una amarilla en el arreglo gris, la borra del mismo
    for (int i = 0; i < COLUMNAS; i++){
        char letra = tablero[filaActual][i].letra;
        char color = tablero[filaActual][i].color;
        if (color == 'A') {
            for (int k = 0; k < cgrises; k++) {
                if (grises[k] == letra) {
                    for (int l = k; l < cgrises - 1; l++) {
                        grises[l] = grises[l + 1];
                    }
                    cgrises--;
                    break;
                }
            }
        }
    }

    //bucle gnral q recorre todas las palabras
    for (int i = 0; i < totalPalabras; i++) {
        char* palabraActual = palabras[i].palabra;
        int esValida = 1;


        //verifica si tiene una letra gris y saltea la palabra
        for (int j = 0; j < cgrises; j++) {
            if (strchr(palabraActual, grises[j]) != NULL) {
                esValida = 0;
                eliminarIndices[eliminarCount++] = i;  //marco para borrar dsp
                break;
            }
        }

        if (!esValida) continue;

        //comprobar la posicion de las letras verdes y amarillas
        for (int j = 0; j < COLUMNAS; j++) {
            char letra = tablero[filaActual][j].letra;
            char color = tablero[filaActual][j].color;

            if (color == 'V' && letra != palabraActual[j]) {
                esValida = 0;
                eliminarIndices[eliminarCount++] = i;
                break;
            }

            if (color == 'A') {
                if (letra == palabraActual[j] || strchr(palabraActual, letra) == NULL) {
                    esValida = 0;
                    eliminarIndices[eliminarCount++] = i;
                    break;
                }
            }
        }

        //comparar frec y elegir la q tenga mayor frecuencia(si hay 2 iguales elige la q aparezca primero)
        if (esValida && palabras[i].frecuencia > mejorFrecuencia) {
            if (sugerencia) {
                free(sugerencia);
            }
            mejorFrecuencia = palabras[i].frecuencia;
            sugerencia = strdup(palabraActual);
        }
    }

    //borrar las marcadas
    for (int i = eliminarCount - 1; i >= 0; i--) {
        eliminarPalabra(palabras[eliminarIndices[i]].palabra);
    }
    
    return sugerencia;
}

char* palabraRandom() {
    if (totalPalabras <= 0) {
        return NULL;
    }
    srand(time(NULL));

    int indiceAleatorio = rand() % totalPalabras;
    return palabras[indiceAleatorio].palabra;
}