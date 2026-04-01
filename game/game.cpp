#include <iostream>
#include <cstdlib>
#include <curses.h>
#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "frogCharacters.h"
#include "endTimeEndScreen.h"
#include "levelMenu.h"
#include "winEndScreen.h"
#include "carCollisionEndScreen.h"
#include "carCharacters.h"
#include "initPair.h"
#include "fileRead.h"
#include "obstacleCreation.h"
#include "zabuszek.h"
#include "friendlyCarCharacters.h"
#include "uberCharacters.h"
#include "rankingSystem.h"
#include "stork.h"
#include "storkCollisionEndScreen.h"
#include "gameOverScreen.h"
#include "settingMenu.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#define frogHeight 3
#define frogWidth 3
#define carHeight 3
#define carWidth 6
using namespace std;
void setBackgroundColor(int color) {    //Kolory tła 
    attron(COLOR_PAIR(color));
}
void delay(int ms) {    //Mała przerwa aby gra nie szła nieskończenie szybko
    clock_t startTime = clock();
    while (clock() < startTime + ms * (CLOCKS_PER_SEC / 1000)) {

    
}
}
void moveToPosition(int x, int y) {
    move(y - 1, x - 1);
}
void move(Zabuszek& zabuszek, const char** frogCharacter = nullptr, int HEIGHT = 3) {
    static const char* defaultSprite[] = {
       "* *",
       "---",
       "^*^"
    
};
    if (frogCharacter == nullptr) {
        frogCharacter = defaultSprite;
    
}
    attron(COLOR_PAIR(green));
    for (int i = 0; i < HEIGHT; i++) {
        moveToPosition(zabuszek.x, zabuszek.y + i);
        printw("%s", frogCharacter[i]);     //Tworzenie żaby na ekran
    
}
    attroff(COLOR_PAIR(green));
}
bool checkCollisions(Zabuszek zabuszek, const int wroomCount, Wroom cars[], int HEIGHT, int WIDTH, bool playerControlOff) {
    if (playerControlOff) return false;     //Jeżeli żaba jest nieruszalna przez gracza to nie istnieją kolizje (przy samochodzie Ubera)
    for (int i = 0; i < wroomCount; i++) {
        if (zabuszek.x < cars[i].x + carWidth &&        //
            zabuszek.x + frogWidth > cars[i].x &&       // Sprawdzanie czy współrzędne samochodu są wspólne z współrzędami żaby
            zabuszek.y < cars[i].y + carHeight &&       //
            zabuszek.y + frogHeight > cars[i].y) {      //
            return true;
        
}
    
}
    return false;
}
void endFlag(int HEIGHT, int WIDTH) {   //Rysowanie flagi mety
    for (int y = 1; y <= 3; y++) {
        for (int x = 0; x < WIDTH; x++) {
            moveToPosition(x + 1, y);
            if (y == 1 || y == 3) {
                if ((x / 2) % 2 == 0) {
                    setBackgroundColor(white);
                
}
                else {
                    setBackgroundColor(black);
                
}
            
}
            else if (y == 2) {
                if ((x / 2) % 2 == 0) {
                    setBackgroundColor(black);
                
}
                else {
                    setBackgroundColor(white);
                
}
            
}
            addch(' ');
        
}
    
}
}
void moveWroom(Wroom& car, int WIDTH, Zabuszek& zabuszek) {     //Ruch żaby
    clock_t currentTime = clock();
    double elapse = (double)(currentTime - car.lastMove) / CLOCKS_PER_SEC;
    if (!car.isFriendly || !car.isStopped) {
        if (elapse >= 0.5 / car.speed) {        //Mała przewa między ruchami żaby
            car.lastMove = currentTime;
            if (car.goLeft) {
                car.x -= car.speed;
                if (car.x <= 1) {
                    car.x = 1;
                    car.goLeft = false;
                
}
            
}
            else {
                car.x += car.speed;
                if (car.x >= WIDTH - carWidth + 1) {
                    car.x = WIDTH - carWidth;
                    car.goLeft = true;
                
}
            
}
        
}
    
}
}
void randWroomSpeed(Wroom& car, int& carSpeed) {    //Prędkośc samochodów
    car.speed = rand() % (carSpeed+2) + 1;
}
void initWroom(Wroom cars[], int wroomCount, int HEIGHT, int WIDTH, int& carSpeed, int friendlyWroomCount) {
    int roadHeight = HEIGHT - 6;
    for (int i = 0; i < wroomCount; i++) {
        cars[i].x = rand() % (WIDTH / 5);      //Losowo tworzenie się na randomowych współrzędnych x
        cars[i].y = 4 + rand() % ((roadHeight - 4) / 4) * 4;    //Losowe tworzenie się na randomowych współrzędnych Y
        cars[i].goLeft = rand() % 2;    //Czy samochód idzie albo w lewo albo w prawo
        randWroomSpeed(cars[i], carSpeed);
        cars[i].lastMove = clock();     //Zapisywanie stanu ostatniech ruchów samochodó
        cars[i].isFriendly = (i < friendlyWroomCount);  
        cars[i].isStopped = false;
    
}
}
void moveUberWroom(UberWroom* car, int WIDTH, Zabuszek* zabuszek, bool* playerControlOff);
void wroomCreater(Wroom cars[], int wroomCount, FriendlyWroom* friendlyCars, int friendlyWroomCount, UberWroom* uberCars, int uberCount, int HEIGHT, Zabuszek& zabuszek, bool& playerControlOff) {  //Tworzenie samochody na grę
    for (int i = 0; i < wroomCount; i++) {
        drawWroom(cars[i], HEIGHT, zabuszek);
    
}
    for (int i = 0; i < friendlyWroomCount; i++) {
        drawFriendlyWroom(&friendlyCars[i], HEIGHT, &zabuszek);
    
}
    for (int i = 0; i < uberCount; i++) {
        drawUber(&uberCars[i], HEIGHT, &zabuszek, &playerControlOff);
    
}
}
void wroomMover(Wroom cars[], FriendlyWroom* friendlyCars, UberWroom* uberCars, int friendlyWroomCount, int uberCount, int carCount, int WIDTH, Zabuszek& zabuszek, bool& playerControlOff) {   //Ruszenie samochody na grę
    for (int i = 0; i < carCount; i++) {
        moveWroom(cars[i], WIDTH, zabuszek);
    
}
    for (int i = 0; i < friendlyWroomCount; i++) {
        moveFriendlyWroom(&friendlyCars[i], WIDTH, &zabuszek);
    
}
    for (int i = 0; i < uberCount; i++) {
        moveUberWroom(&uberCars[i], WIDTH, &zabuszek, &playerControlOff);
    
}
}
void dsIF(int x, int y) {       //drawStreetIF -> Aby zmiejszyc ilosc liter w funkcji 'drawStreets', rysowanie drogi
    if ((y - 4) % 4 == 0) {
        moveToPosition(x + 1, y);
        setBackgroundColor(gray);
        addch(' ');
    
}
    else if ((y - 4) % 4 == 1) {
        moveToPosition(x + 1, y);
        if ((x / 5) % 2 == 0) {
            setBackgroundColor(white);
        
}
        else {
            setBackgroundColor(gray);
        
}
        addch(' ');
    
}
    else if ((y - 4) % 4 == 2) {
        moveToPosition(x + 1, y);
        setBackgroundColor(gray);
        addch(' ');
    
}
    else {
        moveToPosition(x + 1, y);
        setBackgroundColor(yellow);
        addch(' ');
    
}
}
void drawStreets(int HEIGHT, int WIDTH, int statusHeight) {     //Rysowanie ulicy
    int roadHeight = HEIGHT - statusHeight;
    for (int y = 4; y < roadHeight - 1; y++) {
        for (int x = 0; x < WIDTH; x++) {
            dsIF(x, y);     
        
}
    
}
    for (int x = 0; x < WIDTH; x++) {
        moveToPosition(x + 1, roadHeight - 1);
        setBackgroundColor(darkBlue);       
        addch(' ');     //Rysowanie dolną pierwszą linię (granicę)
    
}
}
void drawRoads(Zabuszek zabuszek, int HEIGHT, int WIDTH, int statusHeight) {    //Całkowite rysowanie drogi z funkcjami
    int roadHeight = HEIGHT - statusHeight;
    endFlag(HEIGHT, WIDTH);
    const char* metaText = "   M  E  T  A   ";
    int metaTextLength = strlen(metaText), centerX = (WIDTH - metaTextLength) / 2 + 1;
    moveToPosition(centerX, 2);
    attron(COLOR_PAIR(white));
    printw("%s", metaText);
    attroff(COLOR_PAIR(white));
    attroff(A_BOLD);
    drawStreets(HEIGHT, WIDTH, statusHeight);
    const char** currentFrogCharacter = nullptr;
    int frogCharacterHeight = 0;
    frogDirection(zabuszek.direction, &currentFrogCharacter, &frogCharacterHeight);
    move(zabuszek, currentFrogCharacter, frogCharacterHeight);
}
void drawRoadsNoMeta(Zabuszek zabuszek, int HEIGHT, int WIDTH, int statusHeight) {  //Całkowite rysowanie drogi dla poziomu trzeciego
    int roadHeight = HEIGHT - statusHeight;
    const char* text = "PRZEZYJ JAK NAJDLUZEJ";
    for (int y = 1; y < roadHeight - 1; y++) {
        for (int x = 0; x < WIDTH; x++) {
            dsIF(x, y);
        
}
    
}
    attron(COLOR_PAIR(red));
    mvprintw(1, (WIDTH - strlen(text)) / 2, text);
    attroff(COLOR_PAIR(red));
    for (int x = 0; x < WIDTH; x++) {
        moveToPosition(x + 1, roadHeight - 1);
        setBackgroundColor(darkBlue);
        addch(' ');
    
}
    const char** currentFrogCharacter = nullptr;
    int frogCharacterHeight = 0;
    frogDirection(zabuszek.direction, &currentFrogCharacter, &frogCharacterHeight);
    move(zabuszek, currentFrogCharacter, frogCharacterHeight);
}
Zabuszek initZabuszek(int HEIGHT, int WIDTH, int statusHeight) {    //Przygotowanie żaby do działania do gry
    Zabuszek zabuszek;
    zabuszek.x = WIDTH / 2 - 1;
    zabuszek.y = HEIGHT - statusHeight - 3;
    zabuszek.direction = 'w';   //Kierunek żaby
    return zabuszek;
}
void keyMovementZabuszek(Zabuszek& zabuszek, int input, int level, Obstacle& obstacles, int& yCheck, int HEIGHT, int WIDTH, int obstacleCount, int& moveCounter, clock_t& lastMoveTime, clock_t currentTime, Zabuszek newPos, bool playerControlOff, UberWroom* uberCars, int uberCount) {  // Input na ruchy żab
    switch (input) {
    case KEY_UP: case 'w': case 'W':
        if (level == 3 && zabuszek.y <= 4) {    //Trzeci level żeby żaba nie poszła bardziej w górę
            break;
        
}   //zabuszek.direction -> żaba zmienia swój 'sprite' pod względem direction
        if (zabuszek.y > 1) {
            newPos.y--;
            if (canMove(zabuszek, newPos, &obstacles, obstacleCount)) {
                zabuszek = newPos;
                yCheck++;   //Sprawdzać aby żaba nie poszła dalej w dół
                zabuszek.direction = 'w';
                moveCounter++;
                lastMoveTime = currentTime;
            
}
        
}
        break;
    case KEY_DOWN: case 's': case 'S':
        if ((zabuszek.y < HEIGHT - 6) && (yCheck > 0)) {
            newPos.y++;
            if (canMove(zabuszek, newPos, &obstacles, obstacleCount)) {
                zabuszek = newPos;
                yCheck--;   //Sprawdzać aby żaba nie poszła dalej w dół
                zabuszek.direction = 'w';
                moveCounter++;
                lastMoveTime = currentTime;
            
}
        
}
        break;
    case KEY_LEFT: case 'a': case 'A':
        if (zabuszek.x > 1) {
            newPos.x -= 2;
            if (canMove(zabuszek, newPos, &obstacles, obstacleCount)) {
                zabuszek = newPos;
                zabuszek.direction = 'a';
                moveCounter++;
                lastMoveTime = currentTime;
            
}
        
}
        break;
    case KEY_RIGHT: case 'd': case 'D':
        if (zabuszek.x < WIDTH - 3) {
            newPos.x += 2;
            if (canMove(zabuszek, newPos, &obstacles, obstacleCount)) {
                zabuszek = newPos;
                zabuszek.direction = 'd';
                moveCounter++;
                lastMoveTime = currentTime;
            
}
        
}
        break;
    case 'e': case 'E':
        UberInteraction(uberCars, uberCount, &zabuszek, &playerControlOff);
        return;
    default:
        return;
    
}
}
void moveZabuszek(Zabuszek& zabuszek, int HEIGHT, int WIDTH, int input, int& yCheck, int& moveCounter, clock_t& lastMoveTime, Obstacle& obstacles, int obstacleCount, bool playerControlOff, UberWroom* uberCars, int uberCount, int level) {   //Całkowity ruch żaby
    if (playerControlOff) {
        return;
    
}
    Zabuszek newPos = zabuszek;
    const char** frogCharacter = nullptr;
    int frogCharacterHeight = 0;
    const double moveCooldown = 0.10;
    clock_t currentTime = clock();
    double elapsedTime = (double)(currentTime - lastMoveTime) / CLOCKS_PER_SEC;
    if (elapsedTime >= moveCooldown) {
        keyMovementZabuszek(zabuszek, input, level, obstacles, yCheck, HEIGHT, WIDTH, obstacleCount, moveCounter, lastMoveTime, currentTime, newPos, playerControlOff, uberCars, uberCount);
        frogDirection(zabuszek.direction, &frogCharacter, &frogCharacterHeight);
        if (frogCharacter) {
            attron(COLOR_PAIR(green));
            for (int i = 0; i < frogCharacterHeight; ++i) {
                mvprintw(zabuszek.y + i, zabuszek.x, frogCharacter[i]);
            
}
            attroff(COLOR_PAIR(green));
        
}
    
}
}
void drawMainMenu(int option, int HEIGHT, int WIDTH) {  //Rysowanie menu głównego
    const char* options[] = { "---> Rozpocznij gre", "---> Ranking", "---> Ustawienia", "---> Wyjdz z gry" 
};
    int n = 4;
    clear();
    mvprintw((HEIGHT / 2) - 5, (WIDTH - 14) / 2, "-=- MENU -=-");
    for (int i = 0; i < n; i++) {
        if (i == option) {
            attron(A_REVERSE);
        
}
        mvprintw((HEIGHT / 2) + i, WIDTH / 2 - strlen(options[i]) / 2, "%s", options[i]);
        if (i == option) {
            attroff(A_REVERSE);
        
}
    
}
}
void gsInput(int input, int HEIGHT, int WIDTH, bool& running, Zabuszek& zabuszek, int& yCheck, int& moveCounter, clock_t& lastMoveTime, Obstacle& obstacles, int& obstacleCount, bool& playerControlOff, UberWroom* uberCars, int uberCount, int level) {   //Pobranie input w GameStart
    if (input == KEY_RESIZE) {
        getmaxyx(stdscr, HEIGHT, WIDTH);    //Rozmiar terminalu
        clear();
    
}
    else if (input == 27) {
        mvprintw(HEIGHT - 3, (WIDTH / 2) - (strlen("Wyjsc z gry?  T/N") / 2), "%s", "Wyjsc z gry?  T/N");
        while (true) {
            int confirm = getch();
            if ((confirm == 'T') || (confirm == 't')) {
                running = false;
                break;
            
}
            else if ((confirm == 'N') || (confirm == 'n')) {
                running = true;
                mvprintw(HEIGHT - 3, (WIDTH / 2) - (strlen("                 ") / 2), "%s", "                 ");
                refresh();
                break;
            
}
        
}
    
}
    else {
        moveZabuszek(zabuszek, HEIGHT, WIDTH, input, yCheck, moveCounter, lastMoveTime, obstacles, obstacleCount, playerControlOff, uberCars, uberCount, level);
    
}
}
void winResults(int HEIGHT, int WIDTH, int& moveCounter, float& elapsedTime) {  //Wyniki podane na końcu gry wygranej
    mvprintw(HEIGHT - 12, (WIDTH / 2) - 6, "WYNIKI: ");
    mvprintw(HEIGHT - 10, (WIDTH / 2) - 12, "Czas: %.3f", elapsedTime);
    mvprintw(HEIGHT - 9, (WIDTH / 2) - 12, "Ilosc ruchow: %d", moveCounter);
}
void endScreenLevelOne(Zabuszek zabuszek, const int wroomCount, Wroom cars[], int HEIGHT, int WIDTH, bool& running, int& moveCounter, float& elapsedTime, int& carSpeed, int& carAmount, float& time, bool playerControlOff) {  //Ekran końcowy dla poziomu 1
    if (!playerControlOff) {
        for (int i = 0; i < wroomCount; i++) {
            if (zabuszek.x<cars[i].x + carWidth && zabuszek.x + frogWidth > cars[i].x && zabuszek.y < cars[i].y + carHeight && zabuszek.y + frogHeight > cars[i].y) { // Kolizja z samochodem
                carCollisionEndScreen(HEIGHT, WIDTH);
                nodelay(stdscr, FALSE);
                int input = getch();
                switch (input) {
                case 'r':
                    clear();
                    gameStartLevelOne(HEIGHT, WIDTH, carSpeed, carAmount, time);
                
}
                running = false;
                break;
            
}
        
}
    
}
    if (zabuszek.y <= 1) {  //wygranie
        winEndScreen(HEIGHT, WIDTH);
        winResults(HEIGHT, WIDTH, moveCounter, elapsedTime);
        saveScore(elapsedTime, moveCounter, 1);
        nodelay(stdscr, FALSE);
        int input = getch();
        switch (input) {
        case 'r':
            clear();
            gameStartLevelOne(HEIGHT, WIDTH, carSpeed, carAmount, time);
        
}
        running = false;
    
}
}
void endScreenLevelTwo(Zabuszek zabuszek, const int wroomCount, Wroom cars[], int HEIGHT, int WIDTH, bool& running, int& moveCounter, float& elapsedTime, int& carSpeed, int& carAmount, float& time, bool playerControlOff) {  //Ekran końcowy dla poziomu 2
    if (!playerControlOff) {
        for (int i = 0; i < wroomCount; i++) {
            if (zabuszek.x < cars[i].x + carWidth && zabuszek.x + frogWidth > cars[i].x && zabuszek.y < cars[i].y + carHeight && zabuszek.y + frogHeight > cars[i].y) { //Koalizja
                carCollisionEndScreen(HEIGHT, WIDTH);
                nodelay(stdscr, FALSE);
                int input = getch();
                switch (input) {
                case 'r':
                    clear();
                    gameStartLevelTwo(HEIGHT, WIDTH, carSpeed, carAmount, time);
                
}
                running = false;
                break;
            
}
        
}
    
}
    if (zabuszek.y <= 1) {
        winEndScreen(HEIGHT, WIDTH);
        winResults(HEIGHT, WIDTH, moveCounter, elapsedTime);
        saveScore(elapsedTime, moveCounter, 2);
        nodelay(stdscr, FALSE);
        int input = getch();
        switch (input) {
        case 'r':
            clear();
            gameStartLevelTwo(HEIGHT, WIDTH, carSpeed, carAmount, time);
        
}
        running = false;
    
}
}
void statusLevelOne(int HEIGHT, int WIDTH, Zabuszek& zabuszek, float& timeLeft, int& moveCounter, int& wroomCount) {    //Pokazanie statusu dla poziomu 1
    for (int i = 0; i < (WIDTH/2)-5; i++) {
        mvprintw(HEIGHT - 7, i + 1, "=");
    
}
    mvprintw(HEIGHT - 7, (WIDTH/2)-5, "Level One");
    for (int i = (WIDTH / 2) + 3; i < WIDTH; i++) {
        mvprintw(HEIGHT - 7, i + 1, "=");
    
}
    mvprintw(HEIGHT - 1, 1, "Frog coor: %d %d", zabuszek.x, zabuszek.y);
    mvprintw(HEIGHT - 1, WIDTH - 28, "Daniel Swietlinski, s203177");
    mvprintw(HEIGHT - 6, 1, "Time: %.3f", timeLeft);
    mvprintw(HEIGHT - 5, 1, "Ruchy: %d", moveCounter);
    mvprintw(HEIGHT - 3, 1, "Car count: %d", wroomCount);
}
void statusLevelTwo(int HEIGHT, int WIDTH, Zabuszek& zabuszek, float& timeLeft, int& moveCounter) { //Pokazanie statusu dla poziomu 2
    for (int i = 0; i < (WIDTH / 2) - 5; i++) {
        mvprintw(HEIGHT - 7, i + 1, "=");
    
}
    mvprintw(HEIGHT - 7, (WIDTH / 2) - 5, "Level Two");
    for (int i = (WIDTH / 2) + 3; i < WIDTH; i++) {
        mvprintw(HEIGHT - 7, i + 1, "=");
    
}
    mvprintw(HEIGHT - 1, 1, "Frog coor: %d %d", zabuszek.x, zabuszek.y);
    mvprintw(HEIGHT - 1, WIDTH - 28, "Daniel Swietlinski, s203177");
    mvprintw(HEIGHT - 6, 1, "Time: %.3f", timeLeft);
    mvprintw(HEIGHT - 5, 1, "Ruchy: %d", moveCounter);
}
void statusLevelThree(int HEIGHT, int WIDTH, Zabuszek& zabuszek, float& survivalTime, int& moveCounter) {  //Pokazanie statusu dla poziomu 3
    for (int i = 0; i < (WIDTH / 2) - 6; i++) {
        mvprintw(HEIGHT - 7, i + 1, "=");
    
}
    mvprintw(HEIGHT - 7, (WIDTH / 2) - 5, "Level Three");
    for (int i = (WIDTH / 2) + 5; i < WIDTH; i++) {
        mvprintw(HEIGHT - 7, i + 1, "=");
    
}
    mvprintw(HEIGHT - 1, 1, "Frog coor: %d %d", zabuszek.x, zabuszek.y);
    mvprintw(HEIGHT - 1, WIDTH - 28, "Daniel Swietlinski, s203177");
    mvprintw(HEIGHT - 6, 1, "Survival Time: %.3f", survivalTime);
    mvprintw(HEIGHT - 5, 1, "Moves: %d", moveCounter);
    mvprintw(HEIGHT - 4, 1, "Speed Multiplier: %d", (int)(survivalTime / 10) + 1);
}
void mainMenu(int HEIGHT, int WIDTH) {
    int carSpeed = 1, carAmount = 3, option = 0, obstacleAmount = 0;
    float time = 30.0;
    fileRead("gameParameters.txt", &carSpeed, &carAmount, &time, &obstacleAmount);  //Pobieranie z pliku dane 
    const int n = 4;
    bool inMenu = true;
    while (inMenu) {
        drawMainMenu(option, HEIGHT, WIDTH);
        int input = getch();
        switch (input) {
        case 'w': case 'W': case KEY_UP:
            option = (option + n - 1) % n;
            break;
        case 's': case 'S': case KEY_DOWN:
            option = (option + 1) % n;
            break;
        case 27:
            inMenu = false;
            break;
        case '\n': case ' ':
            switch (option) {
            case 0:
                levelMenu(HEIGHT, WIDTH, carSpeed, carAmount, time);
                break;
            case 1:
                rankingMenu(HEIGHT, WIDTH);
                break;
            case 2:
                settingMenu(HEIGHT, WIDTH);
                break;
            case 3:
                inMenu = false;
                break;
            
}
            break;
        
}
    
}
}
int main() {
    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    initPair();
    int HEIGHT, WIDTH;
    getmaxyx(stdscr, HEIGHT, WIDTH);
    mainMenu(HEIGHT, WIDTH);
    endwin();
    return 0;
}
