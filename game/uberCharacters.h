#ifndef uberCharacters_H
#define uberCharacters_H
#include <curses.h>
#include <cstring>
#include <cstdlib>
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
    bool isUber;
    bool isBeingDriven;
    clock_t drivingStartTime; 
} UberWroom;
void drawUber(UberWroom* car, int HEIGHT, Zabuszek* zabuszek, bool* playerControlOff) {
    if (!car || !zabuszek) return;
    static bool showMessage = false;
    const char carLeft[3][7] = {
        " <[]| ",
        "<UBER|",
        " 0  0 "
    
};
    const char carRight[3][7] = {
        " |[]> ",
        "|UBER>",
        " 0  0 "
    
};
    int xDiff = abs(car->x - zabuszek->x);  //Odległość (Różnica) od współrzędnych x samochodu i żaby
    int yDiff = abs(car->y - zabuszek->y);  //Odległość (Różnica) od współrzędnych y samochodu i żaby
    if (xDiff <= 7 && yDiff <= 6) { //Czy odległość jest wystarczająco daleko
        car->isStopped = true;  //Zatrzymuje się samochód aż dopóki żaba odejdzie
        car->isUber = true; //Możliwość przesunięcia żaby
        if (!car->isBeingDriven) {
            mvprintw(HEIGHT - 2, 30, "Nacisnij 'e' aby jezdzic");
            showMessage = true;
        
}
    
}
    else {
        car->isStopped = false;
        car->isUber = false;
        if (showMessage) {
            mvprintw(HEIGHT - 2, 30, "                         ");  //Czyśczenie tekstu wcześniejszego na przycisk 'e'
            showMessage = false;
        
}
    
}
    if (car->y + 2 <= HEIGHT - 1) { //Tworzenie samochodu ubera pod względem kierunku
        const char(*currentSprite)[7] = car->goLeft ? carLeft : carRight;
        for (int i = 0; i < 3; i++) {
            moveToPosition(car->x, car->y + i);
            for (int j = 0; currentSprite[i][j] != '\0'; j++) {
                if (currentSprite[i][j] != ' ') {   //Kolorowanie jedynie samochodu z znaczkami, nie spacjami
                    attron(COLOR_PAIR(green));
                    addch(currentSprite[i][j]);
                    attroff(COLOR_PAIR(green));
                
}
                else {
                    addch(' ');
                
}
            
}
        
}
    
}
}
void moveUberWroom(UberWroom* car, int WIDTH, Zabuszek* zabuszek, bool* playerControlOff) {     //Ruch samochodu ubera całkowitego
    if (!car || !zabuszek) return;
    clock_t currentTime = clock();
    double elapse = (double)(currentTime - car->lastMove) / CLOCKS_PER_SEC;
    if (car->isBeingDriven) {   //Samochód bierze żabę przez 3 sekundy ze sobą
        double drivingDuration = (double)(currentTime - car->drivingStartTime) / CLOCKS_PER_SEC;
        mvprintw(28, 30, "Czas jezdzenia: %.1f/3.0", drivingDuration);  //Debugger text na długość jazdy
        refresh();
        *playerControlOff = true;   //Żaba się nie ruszy + jest niezniszczalny
        car->isStopped = false;
        int originalSpeed = car->speed;
        car->speed *= 2;
        if (drivingDuration >= 3.0) {    //Czas jazdy 3 sekundy
            car->isBeingDriven = false;
            *playerControlOff = false;
            car->speed = originalSpeed;
        
}
        else {  /*Żaba idzie razem z uberem -> funkcja cała else*/
            if (elapse >= 0.5 / car->speed) {
                car->lastMove = currentTime;
                if (car->goLeft) {
                    car->x -= car->speed;
                    if (car->x <= 1) {  //Zmiany sprite samochodu na inny kierunek
                        car->x = 1;
                        car->goLeft = false;
                    
}
                
}
                else {
                    car->x += car->speed;
                    if (car->x >= WIDTH - 6 + 1) {  //Zmiany sprite samochodu na inny kierunek
                        car->x = WIDTH - 6;
                        car->goLeft = true;
                    
}
                
}
            
}
            zabuszek->x = car->x + (car->goLeft ? -3 : 3);
            zabuszek->y = car->y;
        
}
        car->speed = originalSpeed;
    
}
    else if (!car->isStopped) { /*Przesunięcie żaby do samochodu*/
        if (elapse >= 0.5 / car->speed) {
            car->lastMove = currentTime;
            if (car->goLeft) {
                car->x -= car->speed;
                if (car->x <= 1) {  //Zmiany sprite samochodu na inny kierunek
                    car->x = 1;
                    car->goLeft = false;
                
}
            
}
            else {
                car->x += car->speed;
                if (car->x >= WIDTH - 6 + 1) {  //Zmiany sprite samochodu na inny kierunek
                    car->x = WIDTH - 6;
                    car->goLeft = true;
                
}
            
}
        
}
    
}
}
void initUberWroom(UberWroom* UberCars, int UberCount, int HEIGHT, int WIDTH, int* carSpeed) { //Przygotwanie ubera do gry
    for (int i = 0; i < UberCount; i++) {
        UberCars[i].x = rand() % (WIDTH / 5);   //Losowe miejsce w losowym punkcie X
        UberCars[i].y = 4 + rand() % ((HEIGHT - 10) / 4) * 4; //Losowe miejsce w losowym punkcie Y
        UberCars[i].goLeft = rand() % 2; //Czy samochód idzie w lewo czy w prawo
        UberCars[i].speed = rand() % (*carSpeed + 2) + 1;   //Prędkośc samochodu
        UberCars[i].lastMove = clock(); //Zapisywanie ostatniego ruchu samochodu
        UberCars[i].isStopped = false;
        UberCars[i].isUber = false;
        UberCars[i].isBeingDriven = false;
    
}
}
void UberInteraction(UberWroom* UberCars, int UberCount, Zabuszek* zabuszek, bool* playerControlOff) {  //Po naciśnieciu 'e' przy uberze
    for (int i = 0; i < UberCount; i++) {
        int xDiff = abs(UberCars[i].x - zabuszek->x);
        int yDiff = abs(UberCars[i].y - zabuszek->y);
        if (xDiff <= 7 && yDiff <= 6 && UberCars[i].isUber && !UberCars[i].isBeingDriven) {
            UberCars[i].isBeingDriven = true;
            UberCars[i].isStopped = false;
            UberCars[i].drivingStartTime = clock();
            *playerControlOff = true;
            zabuszek->x = UberCars[i].x + (UberCars[i].goLeft ? -3 : 3);
            zabuszek->y = UberCars[i].y;
            break;
        
}
    
}
}
#endif 
