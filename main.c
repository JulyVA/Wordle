#include "jugable.h"
#include "jugador.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <palabra secreta de %d caracteres>\n", argv[0],COLUMNAS);
        return 1;
    }
    if (strlen(argv[1]) != COLUMNAS) {
        printf("La palabra secreta debe tener exactamente %d caracteres.\n", COLUMNAS);
        return 1;
    }
    for (int i = 0; argv[1][i]; i++) {
        argv[1][i] = toupper(argv[1][i]);
    }

    cargarBaseDatos("palabras.txt");
    int resultado = jugable(argv[1]);
    
    liberarMemoria();

    return resultado;
}
