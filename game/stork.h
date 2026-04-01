#ifndef stork_H
#define stork_H
#include <curses.h>
#include "zabuszek.h"
typedef struct {
        int x;
        int y;
        clock_t lastMove;
}Stork;
void drawStork(Stork* stork) {   //Rysowanie bociana
        const char storkSprite[3][5] = {
                "^v^",
                "-|-",
                " ^ "
        
};
        attron(COLOR_PAIR(lightBlue));
        for (int i = 0; i < 3; i++) {
                moveToPosition(stork->x, stork->y + i);
                printw("%s", storkSprite[i]);
        
}
        attroff(COLOR_PAIR(lightBlue));
}
void initStork(Stork* stork, int HEIGHT, int WIDTH) {    //Przygotowanie bociana
        bool spawnRight = rand() % 2;   //Bocian się tworzy albo w dolnym prawym rogu albo w dolnym lewym rogu
        if (spawnRight) {
                stork->x = WIDTH - 5;
        
}
        else {
                stork->x = 1;
        
}
        stork->y = HEIGHT - 9;
        stork->lastMove = clock();
}
void moveStork(Stork* stork, Zabuszek* zabuszek, bool playerControlOff) {        //Ruszenie bociana
        clock_t currentTime = clock();
        double elapsed = (double)(currentTime - stork->lastMove) / CLOCKS_PER_SEC;
        if (elapsed >= 0.50) {
                stork->lastMove = currentTime;
                int dx = zabuszek->x - stork->x;        //Odleglość współrzędnych X z bociana do żaby
                int dy = zabuszek->y - stork->y;        //Odleglość współrzędnych Y z bociana do żaby
                if (dx > 0) stork->x++;         //Bocian się ruszy w kierunku żaby
                if (dx < 0) stork->x--;         //Bocian się ruszy w kierunku żaby
                if (dy > 0) stork->y++;         //Bocian się ruszy w kierunku żaby
                if (dy < 0) stork->y--;         //Bocian się ruszy w kierunku żaby
        
}
}
bool checkStorkCollision(Stork* stork, Zabuszek* zabuszek, bool playerControlOff) {      //Sprawdzanie koalizji bociana z żabą
        if (!stork || !zabuszek || playerControlOff) return false;      
        return (abs(stork->x - zabuszek->x) < 4 && abs(stork->y - zabuszek->y) < 3);    //Jeżeli true, to koalizja jest, false to koalizja nie ma
}
#endif
