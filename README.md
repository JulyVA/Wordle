# Wordle - Julián Vaccari y Francisco Yucovsky - 2024

## Descripción General

Este proyecto implementa una versión del juego Wordle en C, donde el objetivo es adivinar una palabra secreta de 5 letras. El jugador puede elegir si desea asistencia para jugar o no, y si quiere ingresar la primera palabra o utilizar una palabra aleatoria de la base de datos. Se emplea un sistema de colores para indicar el estado de las letras: verde para correctas en posición y letra, amarillo para correctas en letra pero en posición incorrecta, y gris para incorrectas.

## Compilación

gcc main.c jugador.c jugable.c ed2.c -Wall -Wextra -o wordle

## Ejecución

./wordle 'palabra secreta de 5 caracteres'

El argumento `'palabra secreta de 5 caracteres'` corresponde a la palabra que el jugador deberá adivinar durante la partida. Esta palabra debe ser de exactamente 5 letras.

## Para el que lee el código por primera vez

Se recomienda comenzar por `main.c`, seguir por las funciones de `jugable.c` y `jugador.c`, y luego revisar `ed2.c`. Esto facilita la comprensión general antes de entrar en detalles.

## Criterio de Desempate

Cuando dos palabras de la base de datos tienen la misma frecuencia, se selecciona la que aparece primero en la lista de palabras. Este criterio simplifica la implementación y garantiza una selección consistente.

## Representación de datos

- **Palabra secreta**: guardada en un array de caracteres y convertida a mayúsculas para un manejo uniforme.
- **Tablero del juego**: un arreglo bidimensional donde se almacenan las letras y los colores asociados a cada intento.
- **Base de datos de palabras**: una estructura de datos que almacena palabras con su frecuencia de uso para sugerir jugadas.

## Estructuras de Datos Utilizadas

- **Arreglo de estructuras `Letra`**: para representar cada letra del tablero y su estado (correcta, incorrecta, posición).
- **Lista enlazada de palabras**: para la base de datos de palabras, permitiendo agregar y buscar sugerencias de forma eficiente.