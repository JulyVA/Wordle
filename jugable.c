#include "jugable.h"

#include <conio.h>

int jugable(char *palabraSecreta) {
    system(limpiar);
    int b = 1;
    char bot;
    while (b) {
        printf("Desea jugar con asistencia? [S/N]: ");
        if (scanf(" %c", &bot) != 1) {
            while (getchar() != '\n');
            printf("Por favor ingrese 'S' o 'N'.\n");
        } else {
            bot = toupper(bot);
            if (bot == 'S' || bot == 'N') {
                b = 0;
            } else {
                printf("Por favor ingrese 'S' o 'N'.\n");
            }
        }

        while (getchar() != '\n');
    }

    char bot2;
    b=1;
    if (bot == 'S'){
        while (b) {
            printf("Desea ingresar la primer palabra (S) o que se elija de la base de datos (N)? [S/N]: ");
            if (scanf(" %c", &bot2) != 1) {
                while (getchar() != '\n');
                printf("Por favor ingrese 'S' o 'N'.\n");
            } else {
                bot2 = toupper(bot2);
                if (bot2 == 'S' || bot2 == 'N') {
                    b = 0;
                } else {
                    printf("Por favor ingrese 'S' o 'N'.\n");
                }
            }
            while (getchar() != '\n');
        }
    }

    Letra** tablero = malloc(FILAS * sizeof(Letra*));
    for (int i = 0; i < FILAS; i++) {
        tablero[i] = malloc(COLUMNAS * sizeof(Letra));
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j].letra = ' ';
            tablero[i][j].color = ' ';
        }
    }

    int filaActual = 0;

    if (bot == 'S') {
        if(bot2 == 'S'){
            rellenar(tablero, filaActual,palabraSecreta);
        } else {
            for (int j = 0; j < COLUMNAS; j++) {
                char* palabraR=palabraRandom();
                tablero[filaActual][j].letra = palabraR[j];
            }
            elegirColor(tablero, filaActual, palabraSecreta);
            imprimirTablero(tablero, filaActual, COLUMNAS - 1);
        }

        if (comprobar(tablero, filaActual)) {
            printf("Felicitaciones, ganaste en el primer intento!\n");
            for (int j = 0; j < FILAS; j++)
                free(tablero[j]);
            free(tablero);
            return 0;
        }
        filaActual++;
    }

    for (int i = 0; i < FILAS; i++) {
        if (bot == 'S') {
            sleep(1);
            char* sugerencia = obtenerSugerencia(tablero, filaActual-1);
            for (int j = 0; j < COLUMNAS; j++) {
                tablero[filaActual][j].letra = toupper(sugerencia[j]);
            }
            elegirColor(tablero, filaActual, palabraSecreta);
            imprimirTablero(tablero, filaActual, COLUMNAS - 1);
            free(sugerencia);
        } else {
            rellenar(tablero, filaActual,palabraSecreta);
        }

        if (comprobar(tablero, filaActual)) {
            printf("Felicitaciones, ganaste en %d intentos!\n", filaActual + 1);
            for (int j = 0; j < FILAS; j++)
                free(tablero[j]);
            free(tablero);
            return 0;
        }

        filaActual++;

        if(filaActual==FILAS){
            printf("Perdiste, volve a intentarlo!");
            for (int i = 0; i < FILAS; i++)
                free(tablero[i]);
            free(tablero);
            return 0;
        }
    }
    return 0;
}

void elegirColor(Letra** tablero, int filaActual, const char* objetivo) {
    int marcadas_objetivo[COLUMNAS] = {0};
    int marcadas_tablero[COLUMNAS] = {0};

    for (int j = 0; j < COLUMNAS; j++) {
        if (tablero[filaActual][j].letra == objetivo[j]) {
            tablero[filaActual][j].color = 'V';
            marcadas_objetivo[j] = 1;
            marcadas_tablero[j] = 1;
        }
    }

    for (int j = 0; j < COLUMNAS; j++) {
        if (!marcadas_tablero[j]) {
            for (int k = 0; k < COLUMNAS; k++) {
                if (!marcadas_objetivo[k] && tablero[filaActual][j].letra == objetivo[k]) {
                    tablero[filaActual][j].color = 'A';
                    marcadas_objetivo[k] = 1;
                }
            }
        }
    }

    for (int j = 0; j < COLUMNAS; j++) {
        if (tablero[filaActual][j].color != 'V' && tablero[filaActual][j].color != 'A') {
            tablero[filaActual][j].color = 'G';
        }
    }
}

void imprimirTablero(Letra** tablero, int filaActual, int columnaActual) {
    system(limpiar);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i < filaActual || (i == filaActual && j <= columnaActual)) {
                if (tablero[i][j].color == 'V') {
                    printf("| \x1b[32m%c\x1b[0m |", tablero[i][j].letra);
                } else if (tablero[i][j].color == 'A') {
                    printf("| \x1b[33m%c\x1b[0m |", tablero[i][j].letra);
                } else if (tablero[i][j].color == 'G') {
                    printf("| %c |", tablero[i][j].letra);
                } else {
                    printf("| %c |", tablero[i][j].letra);
                }
            } else {
                printf("|   |");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void rellenar(Letra** tablero, int filaActual, const char* palabraSecreta) {
    int i = 0;
    int confirmada = 0;

    imprimirTablero(tablero, filaActual, i);

    while (!confirmada) {
        int ch = _getch();
        if (ch == 8) {  //ASCII 8=borrar
            if (i > 0) {
                i--;
                tablero[filaActual][i].letra = ' ';
                imprimirTablero(tablero, filaActual, i);
            }
        } else if (ch == 13) {  //ASCII 8=borrar
            if (i == COLUMNAS) {
                confirmada = 1;
            }
        } else if (isalpha(ch)) {
            if (i < COLUMNAS) {
                tablero[filaActual][i].letra = toupper(ch);
                imprimirTablero(tablero, filaActual, i);
                i++;
            }
        }
    }

    elegirColor(tablero, filaActual, palabraSecreta);
    imprimirTablero(tablero, filaActual, COLUMNAS - 1);
}

int comprobar(Letra** tablero, int filaActual) {
    for (int j = 0; j < COLUMNAS; j++) {
        if (tablero[filaActual][j].color != 'V') {
            return 0;
        }
    }
    return 1;
}