#ifndef friendlyCarCharacters_H
#define friendlyCarCharacters_H
#include <curses.h>
#include <cstring>
#include <cstdlib>
#include "initPair.h"
typedef struct {
        int x;
        int y;
        bool goLeft;
        int speed;
        clock_t lastMove;
        bool isFriendly;
        bool isStopped;
    bool isActive;
}FriendlyWroom;
void moveToPosition(int x, int y);
void drawFriendlyWroom(FriendlyWroom* car, int HEIGHT, Zabuszek* zabuszek) {
    if (!car || !zabuszek || !car->isActive) return;
    const char carLeft[3][7] = {
        " <[]| ",
        "<++++|",
        " 0  0 "
    
};
    const char carRight[3][7] = {
        " |[]> ",
        "|++++>",
        " 0  0 "
    
};
    int xDiff = abs(car->x - zabuszek->x);
    int yDiff = abs(car->y - zabuszek->y);
    if (xDiff <= 7 && yDiff <= 6) {
        car->isStopped = true;
    
}
    else {
        car->isStopped = false;
    
}
    if (car->y + 2 <= HEIGHT - 1) {
        const char(*currentSprite)[7] = car->goLeft ? carLeft : carRight;
        for (int i = 0; i < 3; i++) {
            moveToPosition(car->x, car->y + i);
            for (int j = 0; currentSprite[i][j] != '\0'; j++) {
                if (currentSprite[i][j] != ' ') {
                    attron(COLOR_PAIR(pink));
                    addch(currentSprite[i][j]);
                    attroff(COLOR_PAIR(pink));
                
}
                else {
                    addch(' ');
                
}
            
}
        
}
    
}
}
void moveFriendlyWroom(FriendlyWroom* car, int WIDTH, Zabuszek* zabuszek) {
    if (!car || !car->isActive) return;
    clock_t currentTime = clock();
    double elapse = (double)(currentTime - car->lastMove) / CLOCKS_PER_SEC;
    if (!car->isStopped) {
        if (elapse >= 0.5 / car->speed) {
            car->lastMove = currentTime;
            if (car->goLeft) {
                car->x -= car->speed;
                if (car->x <= 1) {
                    car->x = 1;
                    car->isActive = false;
                
}
            
}
            else {
                car->x += car->speed;
                if (car->x >= WIDTH - 6 + 1) {
                    car->x = WIDTH - 6;
                    car->isActive = false;
                
}
            
}
        
}
    
}
}
void initFriendlyWroom(FriendlyWroom* friendlyCars, int friendlyCount, int HEIGHT, int WIDTH, int* carSpeed) {
    for (int i = 0; i < friendlyCount; i++) {
        friendlyCars[i].x = rand() % (WIDTH / 5);
        friendlyCars[i].y = 4 + rand() % ((HEIGHT - 10) / 4) * 4;
        friendlyCars[i].goLeft = rand() % 2;
        friendlyCars[i].speed = rand() % (*carSpeed + 2) + 1;
        friendlyCars[i].lastMove = clock();
        friendlyCars[i].isStopped = false;
        friendlyCars[i].isActive = true;
    
}
}
void createNewFriendlyCar(FriendlyWroom* car, int HEIGHT, int WIDTH, int carSpeed) {
    car->isActive = true;
    car->goLeft = rand() % 2;
    car->y = 4 + rand() % ((HEIGHT - 10) / 4) * 4;
    if (car->goLeft) {
        car->x = WIDTH - 6;
    
}
    else {
        car->x = 1; 
    
}
    car->speed = rand() % (carSpeed + 2) + 1;
    car->lastMove = clock();
    car->isStopped = false;
}
#endif
