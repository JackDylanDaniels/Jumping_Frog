#ifndef gameOverScreen_H
#define gameOverScreen_H
#include <curses.h>
#include <cstring>
void gameOverText(int HEIGHT, int WIDTH, float survivalTime) {
        mvprintw((HEIGHT / 2) + 2, (WIDTH / 2) - strlen("Calkowity czas: %1.f") / 2, "Calkowity czas: %.1f", survivalTime);
        mvprintw(HEIGHT - 2, WIDTH - (WIDTH - 2), "Nacisnij cokolwiek aby wrocic do menu");
        mvprintw(HEIGHT - 2, WIDTH - 34, "Nacisnij 'r' aby zagrac ponownie");
}
void gameOverScreen(int HEIGHT, int WIDTH, float survivalTime) {
        clear();
        const char* text[]{
                "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =",
                " GGGGG      A       M       M   EEEEE        OOOOO   V       V  EEEEE  RRRR    !!",
                "G          A A      M M   M M   E           O     O   V     V   E      R   R   !!",
                "G  GG     A   A     M   M   M   EEEE        O     O    V   V    EEEE   RRRR    !!",
                "G    G   AAAAAAA    M       M   E           O     O     V V     E      R   R     ",
                " GGGGG  A       A   M       M   EEEEE        OOOOO       V      EEEEE  R    R  !!",
                "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ="
        
};
        for (int i = 0; i < (sizeof(text) / sizeof(text[0])); i++) {
                mvprintw((HEIGHT / 2) - (sizeof(text) / sizeof(text[0])) + i, (WIDTH / 2) - (strlen(text[i]) / 2), "%s", text[i]);
        
}
        gameOverText(HEIGHT, WIDTH, survivalTime);
        refresh();
        napms(1000);
}
#endif
