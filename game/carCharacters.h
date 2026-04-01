#ifndef carCharacters_H
#define carCharacters_H
#include <curses.h>
#include <cstring>
#include "initPair.h"
#include "zabuszek.h"
typedef struct {
    int x;
    int y;
    bool goLeft;
    int speed;
    clock_t lastMove;
    bool isFriendly;
    bool isStopped;
}Wroom;
void moveToPosition(int x, int y);
void drawWroom(Wroom car, int HEIGHT, Zabuszek& zabuszek) {
    const char carLeft[3][7] = {
        " <[]| ",
        "<____|",
        " 0  0 "
    
};
    const char carRight[3][7] = {
        " |[]> ",
        "|____>",
        " 0  0 "
    
};
    if (car.isFriendly) {
        int xDiff = abs(car.x - zabuszek.x);
        int yDiff = abs(car.y - zabuszek.y);
        if (xDiff <= 2 && yDiff <= 2) {
            car.isStopped = true;
        
}
        else {
            car.isStopped = false;
        
}
    
}
    if (car.y + 2 <= HEIGHT - 1) {
        const char (*currentSprite)[7] = car.goLeft ? carLeft : carRight;
        for (int i = 0; i < 3; i++) {
            moveToPosition(car.x, car.y + i);
            for (int j = 0; currentSprite[i][j] != '\0'; j++) {
                if (currentSprite[i][j] != ' ') {
                    attron(COLOR_PAIR(red));
                    addch(currentSprite[i][j]);
                    attroff(COLOR_PAIR(red));
                
}
                else {
                    addch(' ');
                
}
            
}
        
}
    
}
}
#endif 
