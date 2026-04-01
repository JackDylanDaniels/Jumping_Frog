#ifndef levelTwo_H
#define levelTwo_H
#include "zabuszek.h"
void initWroom(Wroom cars[], int wroomCount, int HEIGHT, int WIDTH, int& carSpeed, int friendlyWroomCount);
Zabuszek initZabuszek(int HEIGHT, int WIDTH, int statusHeight);
void randWroomSpeed(Wroom& car, int& carSpeed);
void drawRoads(Zabuszek zabuszek, int HEIGHT, int WIDTH, int statusHeight);
void wroomCreater(Wroom cars[], int wroomCount, FriendlyWroom* friendlyCars, int friendlyWroomCount, UberWroom* uberCars, int uberCount, int HEIGHT, Zabuszek& zabuszek, bool& playerControlOff);
void wroomMover(Wroom cars[], FriendlyWroom* friendlyCars, UberWroom* uberCars, int friendlyWroomCount, int uberCount, int carCount, int WIDTH, Zabuszek& zabuszek, bool& playerControlOff);
void statusLevelTwo(int HEIGHT, int WIDTH, Zabuszek& zabuszek, float& timeLeft, int& moveCounter);
void gsInput(int input, int HEIGHT, int WIDTH, bool& running, Zabuszek& zabuszek, int& yCheck, int& moveCounter, clock_t& lastMoveTime, Obstacle& obstacles, int& obstacleCount, bool& playerControlOff, UberWroom* uberCars, int uberCount, int level);
void endScreenLevelTwo(Zabuszek zabuszek, const int wroomCount, Wroom cars[], int HEIGHT, int WIDTH, bool& running, int& moveCounter, float& elapsedTime, int& carSpeed, int& carAmount, float& time, bool playerControlOff);
void initLevelTwoComponents(int HEIGHT, int WIDTH, int carSpeed, int carAmount, FriendlyWroom*& friendlyCars, UberWroom*& uberCars, Wroom*& cars, Zabuszek& zabuszek, Obstacle*& obstacles, Stork& stork, int& obstacleCount, int& friendlyWroomCount, int& uberCount, int& wroomCount, int statusHeight) { //Wczytywanie zmiennych
    friendlyWroomCount = carAmount / 3;
    uberCount = carAmount / 3;
    wroomCount = carAmount * 2;
    friendlyCars = new FriendlyWroom[friendlyWroomCount];
    uberCars = new UberWroom[uberCount];
    cars = new Wroom[wroomCount];
    initFriendlyWroom(friendlyCars, friendlyWroomCount, HEIGHT, WIDTH, &carSpeed);
    initUberWroom(uberCars, uberCount, HEIGHT, WIDTH, &carSpeed);
    initStork(&stork, HEIGHT, WIDTH);                                                   //Wszystkie init - przygotowawcze daynych do gry
    initWroom(cars, wroomCount, HEIGHT, WIDTH, carSpeed);
    fileRead("gameParameters.txt", &carSpeed, &carAmount, nullptr, &obstacleCount); //Wczytywanie z pliku
    if (obstacleCount > 0) {
        obstacles = new Obstacle[obstacleCount];
        initObstacles(obstacles, obstacleCount, HEIGHT, WIDTH, statusHeight);
    
}
    zabuszek = initZabuszek(HEIGHT, WIDTH, statusHeight);
}
void levelTwoSpawnManagement(FriendlyWroom* friendlyCars, int friendlyWroomCount, int HEIGHT, int WIDTH, int carSpeed, clock_t& lastFriendlySpawn, const double spawnInterval, clock_t currentTime) {   //Tworzenie friendly samochodów
    double friendlySpawnElapsed = (double)(currentTime - lastFriendlySpawn) / CLOCKS_PER_SEC;
    if (friendlySpawnElapsed >= spawnInterval) {
        for (int i = 0; i < friendlyWroomCount; i++) {
            if (!friendlyCars[i].isActive) {
                createNewFriendlyCar(&friendlyCars[i], HEIGHT, WIDTH, carSpeed);
                lastFriendlySpawn = currentTime;
                break;
            
}
        
}
    
}
}
void handleLevelTwoEnd(int HEIGHT, int WIDTH, bool running, bool endTime, int carSpeed, int carAmount, float time, Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars, Obstacle* obstacles) { //Koniec dla levelu
    nodelay(stdscr, FALSE);
    if (endTime) {
        endTimeEndScreen(HEIGHT, WIDTH);
        int input = getch();
        switch (input) {
        case 27:
            levelMenu(HEIGHT, WIDTH, carSpeed, carAmount, time);
            break;
        case 'r':
            clear();
            gameStartLevelTwo(HEIGHT, WIDTH, carSpeed, carAmount, time);
            break;
        
}
    
}
    delete[] cars;              //Usuwanie pamięci
    delete[] friendlyCars;
    delete[] uberCars;
    if (obstacles) {
        delete[] obstacles;
    
}
}
void initLevelTwoVariables(int& statusHeight, int& yCheck, int& moveCounter, int& wroomCount,
    int& delay, int& obstacleCount, int& friendlyWroomCount, int& uberCount,
    bool& running, bool& endTime, bool& playerControlOff) { // Zainicjonowanie zmiennych
    statusHeight = 6;
    yCheck = 0;
    moveCounter = 0;
    delay = 200;
    obstacleCount = 0;
    running = true;
    endTime = false;
    playerControlOff = false;
}
void handleLevelTwoLoopIF(int HEIGHT, int WIDTH, Wroom* cars, FriendlyWroom* friendlyCars,
    UberWroom* uberCars, Stork& stork, float timeLeft, clock_t currentTime, int statusHeight,
    bool& running, bool& endTime, bool& playerControlOff, int wroomCount, int friendlyWroomCount,
    int uberCount, int& moveCounter, int& yCheck, int obstacleCount, Obstacle* obstacles,
    Zabuszek& zabuszek, float& time, float& elapsedTime, int delay, int carSpeed, int carAmount,
    clock_t& lastCarMove, clock_t& lastMoveTime) {
    if (checkStorkCollision(&stork, &zabuszek, playerControlOff)) { //Sprawdzanie koalizji 
        storkCollisionEndScreen(HEIGHT, WIDTH);
        nodelay(stdscr, FALSE);
        int input = getch();
        if (input == 'r') {
            clear();
            gameStartLevelTwo(HEIGHT, WIDTH, carSpeed, carAmount, time);
        
}
        running = false;
        return;
    
}
    if (timeLeft <= 0) {
        running = false;
        endTime = true;
        return;
    
}
    if ((double)(currentTime - lastCarMove) / CLOCKS_PER_SEC >= delay / 1000.0) {   //Ruszenie samochodó
        wroomMover(cars, friendlyCars, uberCars, friendlyWroomCount, uberCount, wroomCount,
            WIDTH, zabuszek, playerControlOff);
        lastCarMove = currentTime;
    
}
    statusLevelTwo(HEIGHT, WIDTH, zabuszek, timeLeft, moveCounter);
    int input = getch();
    if (input != ERR) {
        gsInput(input, HEIGHT, WIDTH, running, zabuszek, yCheck, moveCounter, lastMoveTime,
            *obstacles, obstacleCount, playerControlOff, uberCars, uberCount, 2);
    
}
    endScreenLevelTwo(zabuszek, wroomCount, cars, HEIGHT, WIDTH, running, moveCounter,
        elapsedTime, carSpeed, carAmount, time, playerControlOff);
}
void handleLevelTwoLoop(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars,
    Stork& stork, int HEIGHT, int WIDTH, int statusHeight, bool& running, bool& endTime,
    bool& playerControlOff, int wroomCount, int friendlyWroomCount, int uberCount,
    int& moveCounter, int& yCheck, int obstacleCount, Obstacle* obstacles,
    Zabuszek& zabuszek, float& time, float& elapsedTime, int delay, int carSpeed,
    int carAmount, clock_t& lastCarMove, clock_t& lastMoveTime,
    clock_t& lastFriendlySpawn, clock_t startTime) { //Tworzenie gry p2
    clock_t currentTime = clock();
    elapsedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC;
    float timeLeft = time - elapsedTime;
    levelTwoSpawnManagement(friendlyCars, friendlyWroomCount, HEIGHT, WIDTH, carSpeed,
        lastFriendlySpawn, 2.0, currentTime);
    drawRoads(zabuszek, HEIGHT, WIDTH, statusHeight);
    wroomCreater(cars, wroomCount, friendlyCars, friendlyWroomCount, uberCars, uberCount,
        HEIGHT, zabuszek, playerControlOff);
    drawObstacles(obstacles, obstacleCount);
    drawStork(&stork);
    moveStork(&stork, &zabuszek, playerControlOff);
    handleLevelTwoLoopIF(HEIGHT, WIDTH, cars, friendlyCars, uberCars, stork, timeLeft,
        currentTime, statusHeight, running, endTime, playerControlOff, wroomCount,
        friendlyWroomCount, uberCount, moveCounter, yCheck, obstacleCount, obstacles,
        zabuszek, time, elapsedTime, delay, carSpeed, carAmount, lastCarMove, lastMoveTime);
    refresh();
}
void initializeLevelTwo(int HEIGHT, int WIDTH, int carSpeed, int carAmount, float gameTime,
    int& statusHeight, int& yCheck, int& moveCounter, int& wroomCount, int& delay,
    int& obstacleCount, int& friendlyWroomCount, int& uberCount, bool& running,
    bool& endTime, bool& playerControlOff, FriendlyWroom*& friendlyCars,
    UberWroom*& uberCars, Wroom*& cars, Obstacle*& obstacles, Stork& stork,
    Zabuszek& zabuszek, clock_t& lastCarMove, clock_t& lastMoveTime,
    clock_t& startTime, clock_t& lastFriendlySpawn, float& time, float& elapsedTime) {  //Tworzenie gry p1
    initLevelTwoVariables(statusHeight, yCheck, moveCounter, wroomCount, delay, obstacleCount,
        friendlyWroomCount, uberCount, running, endTime, playerControlOff);
    initLevelTwoComponents(HEIGHT, WIDTH, carSpeed, carAmount, friendlyCars, uberCars, cars,
        zabuszek, obstacles, stork, obstacleCount, friendlyWroomCount, uberCount,
        wroomCount, statusHeight);
    lastCarMove = clock();
    lastMoveTime = clock();
    startTime = clock();
    lastFriendlySpawn = clock();
    time = gameTime * 0.85;
    nodelay(stdscr, TRUE);
    while (running) {
        handleLevelTwoLoop(cars, friendlyCars, uberCars, stork, HEIGHT, WIDTH, statusHeight,
            running, endTime, playerControlOff, wroomCount, friendlyWroomCount, uberCount,
            moveCounter, yCheck, obstacleCount, obstacles, zabuszek, time, elapsedTime,
            delay, carSpeed, carAmount, lastCarMove, lastMoveTime, lastFriendlySpawn, startTime);
    
}
}
void gameStartLevelTwo(int HEIGHT, int WIDTH, int carSpeed, int carAmount, float gameTime) { //Tworzenie gry p3 (główny)
    int statusHeight, yCheck, moveCounter, wroomCount, delay, obstacleCount,
        friendlyWroomCount, uberCount;
    bool running, endTime, playerControlOff;
    FriendlyWroom* friendlyCars;
    UberWroom* uberCars;
    Wroom* cars;
    Obstacle* obstacles = nullptr;
    Stork stork;
    Zabuszek zabuszek;
    clock_t lastCarMove, lastMoveTime, startTime, lastFriendlySpawn;
    float time, elapsedTime;
    initializeLevelTwo(HEIGHT, WIDTH, carSpeed, carAmount, gameTime, statusHeight, yCheck,
        moveCounter, wroomCount, delay, obstacleCount, friendlyWroomCount, uberCount,
        running, endTime, playerControlOff, friendlyCars, uberCars, cars, obstacles,
        stork, zabuszek, lastCarMove, lastMoveTime, startTime, lastFriendlySpawn,
        time, elapsedTime);
    handleLevelTwoEnd(HEIGHT, WIDTH, running, endTime, carSpeed, carAmount, time,
        cars, friendlyCars, uberCars, obstacles);
}
#endif
