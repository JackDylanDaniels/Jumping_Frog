#ifndef winEndScreen_H
#define winEndScreen_H
#include <curses.h>
#include <cstring>
void winEndScreen(int HEIGHT, int WIDTH) {
        clear();
        const char* text[]{
                "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =",
                "                                                             /       ",
                "W     W  Y     Y  GGGGG  RRRR        A       L      EEEEE  SSSS    !!",
                "W     W   Y   Y  G       R   R      A A      L L    E     S        !!",
                "W  W  W    Y Y   G  GG   RRRR      A   A     L      EEEE   SSS     !!",
                " W W W      Y    G    G  R   R    AAAAAAA  L L      E         S      ",
                "  W W       Y     GGGGG  R    R  A       A   LLLLL  EEEEE SSSS     !!",
                "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ="
        
};
        for (int i = 0; i < (sizeof(text) / sizeof(text[0])); i++) {
                mvprintw((HEIGHT / 2) - (sizeof(text) / sizeof(text[0])) + i, (WIDTH / 2) - (strlen(text[i]) / 2), "%s", text[i]);
        
}
        mvprintw(HEIGHT - 2, WIDTH - (WIDTH - 2), "Nacisnij cokolwiek aby wrocic do menu");
        mvprintw(HEIGHT - 2, WIDTH - 34, "Nacisnij 'r' aby zagrac ponownie");
        refresh();
        napms(1000);
}
#endif
