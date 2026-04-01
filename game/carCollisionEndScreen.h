#ifndef carCollisionEndScreen_H
#define carCollisionEndScreen_H
#include <curses.h>
#include <cstring>
void carCollisionText(int HEIGHT, int WIDTH) {
        mvprintw((HEIGHT / 2) + 2, (WIDTH / 2) - 12, "Powod - rozjechany przez samochod");
        mvprintw(HEIGHT - 2, WIDTH - (WIDTH - 2), "Nacisnij cokolwiek aby wrocic do menu");
        mvprintw(HEIGHT - 2, WIDTH - 34, "Nacisnij 'r' aby zagrac ponownie");
}
void carCollisionEndScreen(int HEIGHT, int WIDTH) {
        clear();
        const char* text[]{
                "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ",
                "                                                                       /      ",
                "PPPP   RRRR    ZZZZZ  EEEEE  GGGGG  RRRR        A       L     EEEEE  SSSS   !!",
                "P   P  R   R      Z   E     G       R   R      A A      L L   E     S       !!",
                "PPPP   RRRR      Z    EEEE  G  GG   RRRR      A   A     L     EEEE   SSS    !!",
                "P      R   R    Z     E     G    G  R   R    AAAAAAA  L L     E         S     ",
                "P      R    R  ZZZZZ  EEEEE  GGGGG  R    R  A       A   LLLLL EEEEE SSSS    !!",
                "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = "
        
};
        for (int i = 0; i < (sizeof(text) / sizeof(text[0])); i++) {
                mvprintw((HEIGHT / 2) - (sizeof(text) / sizeof(text[0])) + i, (WIDTH / 2) - (strlen(text[i]) / 2), "%s", text[i]);
        
}
        carCollisionText(HEIGHT, WIDTH);
        refresh();
        napms(1000);    //Czekać sekundę
}
#endif 
