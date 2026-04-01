#ifndef obstacleCreation_H
#define obstacleCreation_H
#include <cstdlib>
#include <curses.h>
#include "initPair.h"
#include "zabuszek.h"
typedef struct {
        int x;
        int y;
} Obstacle;
void initObstacles(Obstacle obstacles[], int count, int HEIGHT, int WIDTH, int statusHeight) {   //Przygotowanie przeszkodów
        int roadHeight = HEIGHT - statusHeight;
        srand(time(NULL));
        for (int i = 0; i < count; i++) {
                obstacles[i].x = 1 + (rand() % ((WIDTH - 4)/2))*2;
                obstacles[i].y = 3 + (rand() % ((roadHeight-4) / 4)) * 4;
        
}
}
void drawObstacles(Obstacle obstacles[], int count) {
        if (obstacles == NULL || count <= 0) return;
        attron(COLOR_PAIR(darkBlue));
        for (int i = 0; i < count; i++) {
                for (int collum = 0; collum < 4; collum++) {     //Rysowanie przeszkód 
                        moveToPosition(obstacles[i].x + collum, obstacles[i].y);
                        addch('#');
                
}
        
}
        attroff(COLOR_PAIR(darkBlue));
}
bool ifObstacleCollide(Zabuszek zabuszek, Obstacle obstacles[], int count) {     //Blokada na to aby żaba nie mogła przez nie przejść
        if (obstacles == NULL || count <= 0) return false;
        for (int i = 0; i < count; i++) {
                if (zabuszek.x + 2 >= obstacles[i].x && zabuszek.x <= obstacles[i].x + 3 && zabuszek.y + 2 >= obstacles[i].y && zabuszek.y <= obstacles[i].y) {
                        return true;
                
}
        
}
        return false;
}
bool canMove(Zabuszek currentPos, Zabuszek newPos, Obstacle* obstacles, int obstacleCount) {     //Sprawdzać czy żaba może się ruszyć
        Zabuszek tempPos = currentPos;
        tempPos.x = newPos.x;
        tempPos.y = newPos.y;
        return !ifObstacleCollide(tempPos, obstacles, obstacleCount);
}
#endif
