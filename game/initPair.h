#ifndef initPair_H
#define initPair_H
#include <curses.h>
#define gray 2
#define white 3
#define yellow 4
#define darkBlue 1
#define green 5
#define black 227
#define lightBlue 6
#define red 7
#define pink 8
#define purple 9
void initPair() {
    init_pair(darkBlue, COLOR_BLACK, COLOR_BLUE);
    init_pair(gray, COLOR_BLACK, 235);
    init_pair(white, COLOR_BLACK, COLOR_WHITE);
    init_pair(yellow, COLOR_BLACK, COLOR_YELLOW);
    init_pair(green, COLOR_BLACK, COLOR_GREEN);
    init_pair(lightBlue, COLOR_BLACK, COLOR_CYAN);
    init_pair(red, COLOR_BLACK, COLOR_RED);
    init_pair(pink, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(purple, COLOR_BLACK, COLOR_MAGENTA);
}
#endif 
