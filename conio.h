#ifndef CONIO_H
#define CONIO_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

void clrscr() {
    printf("\033[H\033[J"); // Limpia la pantalla
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x); // Mueve el cursor a la posición (x, y)
}

int kbhit(void) {
    struct termios oldt, newt;
    int oldf;
    char ch;
    int is_key_pressed = 0;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    if (read(STDIN_FILENO, &ch, 1) == 1) {
        is_key_pressed = 1;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return is_key_pressed;
}

char getch(void) {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

char _getch(void) {
    return getch(); // Llama a getch() en lugar de definir una nueva lógica
}

#endif
