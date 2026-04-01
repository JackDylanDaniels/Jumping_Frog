#ifndef levelOne_H
#define levelOne_H
#include "zabuszek.h"
void initWroom(Wroom cars[], int wroomCount, int HEIGHT, int WIDTH, int& carSpeed, int friendlyWroomCount = 0);
Zabuszek initZabuszek(int HEIGHT, int WIDTH, int statusHeight);
void randWroomSpeed(Wroom& car, int& carSpeed);
void drawRoads(Zabuszek zabuszek, int HEIGHT, int WIDTH, int statusHeight);
void wroomCreater(Wroom cars[], int wroomCount, FriendlyWroom* friendlyCars, int friendlyWroomCount, UberWroom* uberCars, int uberCount, int HEIGHT, Zabuszek& zabuszek, bool& playerControlOff);
void wroomMover(Wroom cars[], FriendlyWroom* friendlyCars, UberWroom* uberCars, int friendlyWroomCount, int uberCount, int carCount, int WIDTH, Zabuszek& zabuszek, bool& playerControlOff);
void statusLevelOne(int HEIGHT, int WIDTH, Zabuszek& zabuszek, float& timeLeft, int& moveCounter, int& wroomCount);
void gsInput(int input, int HEIGHT, int WIDTH, bool& running, Zabuszek& zabuszek, int& yCheck, int& moveCounter, clock_t& lastMoveTime, Obstacle& obstacles, int& obstacleCount, bool& playerControlOff, UberWroom* uberCars, int uberCount, int level);
void endScreenLevelOne(Zabuszek zabuszek, const int wroomCount, Wroom cars[], int HEIGHT, int WIDTH, bool& running, int& moveCounter, float& elapsedTime, int& carSpeed, int& carAmount, float& time, bool playerControlOff);
void initLevelOneComponents(int HEIGHT, int WIDTH, int carSpeed, int carAmount, FriendlyWroom*& friendlyCars, UberWroom*& uberCars, Wroom*& cars, Zabuszek& zabuszek, Obstacle& obstacles, int& friendlyWroomCount, int& uberCount, int& wroomCount, int& maxWroomCount, int statusHeight) { //Wczytywanie zmiennych
    friendlyWroomCount = carAmount / 3;
    uberCount = carAmount / 3;
    wroomCount = carAmount;
    maxWroomCount = carAmount * 3;
    friendlyCars = new FriendlyWroom[friendlyWroomCount];
    uberCars = new UberWroom[uberCount];
    cars = (Wroom*)malloc(maxWroomCount * sizeof(Wroom));
    initFriendlyWroom(friendlyCars, friendlyWroomCount, HEIGHT, WIDTH, &carSpeed);
    initUberWroom(uberCars, uberCount, HEIGHT, WIDTH, &carSpeed);
    initWroom(cars, wroomCount, HEIGHT, WIDTH, carSpeed, friendlyWroomCount);
    zabuszek = initZabuszek(HEIGHT, WIDTH, statusHeight);
}
void levelOneSpawnManagement(Wroom cars[], FriendlyWroom* friendlyCars, int& wroomCount, int maxWroomCount, int friendlyWroomCount, int HEIGHT, int WIDTH, int carSpeed, clock_t& lastCarSpawn, clock_t& lastFriendlySpawn, const double spawnInterval, clock_t currentTime) {
    double spawnElapsed = (double)(currentTime - lastCarSpawn) / CLOCKS_PER_SEC;
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
    if (spawnElapsed >= 5.0 && wroomCount < maxWroomCount) {
        Wroom newCar;
        newCar.x = rand() % (WIDTH / 5);
        newCar.y = 4 + rand() % ((HEIGHT - 10) / 4) * 4;
        newCar.goLeft = rand() % 2;
        randWroomSpeed(newCar, carSpeed);
        newCar.lastMove = currentTime;
        cars[wroomCount] = newCar;
        wroomCount++;
        lastCarSpawn = currentTime;
    
}
}
void handleLevelOneEnd(int HEIGHT, int WIDTH, bool running, bool endTime, int carSpeed, int carAmount, float time, Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars) {
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
            gameStartLevelOne(HEIGHT, WIDTH, carSpeed, carAmount, time);
            break;
        
}
    
}
    free(cars);
    delete[] friendlyCars;
    delete[] uberCars;
}
void handleLevelOneLoopIF(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars, int HEIGHT, int WIDTH, float timeLeft, clock_t currentTime, int statusHeight, bool& running, bool& endTime, bool& playerControlOff, int& wroomCount, int maxWroomCount, int friendlyWroomCount, int uberCount, int& moveCounter, int& yCheck, int obstacleCount, Obstacle& obstacles, Zabuszek& zabuszek, float& time, float& elapsedTime, int delay, int carSpeed, int carAmount, clock_t& lastCarMove, clock_t& lastMoveTime, clock_t& lastCarSpawn, clock_t& lastFriendlySpawn, clock_t startTime) {
    if (timeLeft <= 0) {
        running = false;
        endTime = true;
        return;
    
}
    if ((double)(currentTime - lastCarMove) / CLOCKS_PER_SEC >= delay / 1000.0) {
        wroomMover(cars, friendlyCars, uberCars, friendlyWroomCount, uberCount, wroomCount, WIDTH, zabuszek, playerControlOff);
        lastCarMove = currentTime;
    
}
    statusLevelOne(HEIGHT, WIDTH, zabuszek, timeLeft, moveCounter, wroomCount);
    int input = getch();
    if (input != ERR) {
        gsInput(input, HEIGHT, WIDTH, running, zabuszek, yCheck, moveCounter, lastMoveTime, obstacles, obstacleCount, playerControlOff, uberCars, uberCount, 1);
    
}
    endScreenLevelOne(zabuszek, wroomCount, cars, HEIGHT, WIDTH, running, moveCounter, elapsedTime, carSpeed, carAmount, time, playerControlOff);
}
void handleLevelOneLoop(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars, int HEIGHT, int WIDTH, int statusHeight, bool& running, bool& endTime, bool& playerControlOff, int& wroomCount, int maxWroomCount, int friendlyWroomCount, int uberCount, int& moveCounter, int& yCheck, int obstacleCount, Obstacle& obstacles, Zabuszek& zabuszek, float& time, float& elapsedTime, int delay, int carSpeed, int carAmount, clock_t& lastCarMove, clock_t& lastMoveTime, clock_t& lastCarSpawn, clock_t& lastFriendlySpawn, clock_t startTime) {
    clock_t currentTime = clock();
    elapsedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC;
    float timeLeft = time - elapsedTime;
    levelOneSpawnManagement(cars, friendlyCars, wroomCount, maxWroomCount, friendlyWroomCount, HEIGHT, WIDTH, carSpeed, lastCarSpawn, lastFriendlySpawn, 2.0, currentTime);
    drawRoads(zabuszek, HEIGHT, WIDTH, statusHeight);
    wroomCreater(cars, wroomCount, friendlyCars, friendlyWroomCount, uberCars, uberCount, HEIGHT, zabuszek, playerControlOff);
    handleLevelOneLoopIF(cars, friendlyCars, uberCars, HEIGHT, WIDTH, timeLeft, currentTime, statusHeight, running, endTime, playerControlOff, wroomCount, maxWroomCount, friendlyWroomCount, uberCount, moveCounter, yCheck, obstacleCount, obstacles, zabuszek, time, elapsedTime, delay, carSpeed, carAmount, lastCarMove, lastMoveTime, lastCarSpawn, lastFriendlySpawn, startTime);
    refresh();
}
void initLevelOneVariables(int& statusHeight, int& yCheck, int& moveCounter, int& wroomCount, int& delay, int& obstacleCount, int& maxWroomCount, int& friendlyWroomCount, int& uberCount, bool& running, bool& endTime, bool& playerControlOff) {
    statusHeight = 6;
    yCheck = 0;
    moveCounter = 0;
    delay = 200;
    obstacleCount = 0;
    running = true;
    endTime = false;
    playerControlOff = false;
}
void initializeLevelOne(int HEIGHT, int WIDTH, int carSpeed, int carAmount, float gameTime,
    int& statusHeight, int& yCheck, int& moveCounter, int& wroomCount, int& delay,
    int& obstacleCount, int& maxWroomCount, int& friendlyWroomCount, int& uberCount,
    bool& running, bool& endTime, bool& playerControlOff, FriendlyWroom*& friendlyCars,
    UberWroom*& uberCars, Wroom*& cars, Obstacle& obstacles, Zabuszek& zabuszek,
    clock_t& lastCarMove, clock_t& lastMoveTime, clock_t& startTime,
    clock_t& lastCarSpawn, clock_t& lastFriendlySpawn, float& time, float& elapsedTime) {
    initLevelOneVariables(statusHeight, yCheck, moveCounter, wroomCount, delay, obstacleCount,
        maxWroomCount, friendlyWroomCount, uberCount, running, endTime, playerControlOff);
    initLevelOneComponents(HEIGHT, WIDTH, carSpeed, carAmount, friendlyCars, uberCars, cars,
        zabuszek, obstacles, friendlyWroomCount, uberCount, wroomCount,
        maxWroomCount, statusHeight);
    lastCarMove = clock();
    lastMoveTime = clock();
    startTime = clock();
    lastCarSpawn = clock();
    lastFriendlySpawn = clock();
    time = gameTime;
    nodelay(stdscr, TRUE);
    while (running) {
        handleLevelOneLoop(cars, friendlyCars, uberCars, HEIGHT, WIDTH, statusHeight, running,
            endTime, playerControlOff, wroomCount, maxWroomCount, friendlyWroomCount, uberCount,
            moveCounter, yCheck, obstacleCount, obstacles, zabuszek, time, elapsedTime, delay,
            carSpeed, carAmount, lastCarMove, lastMoveTime, lastCarSpawn, lastFriendlySpawn,
            startTime);
    
}
}
void gameStartLevelOne(int HEIGHT, int WIDTH, int carSpeed, int carAmount, float gameTime) {
    int statusHeight, yCheck, moveCounter, wroomCount, delay, obstacleCount, maxWroomCount,
        friendlyWroomCount, uberCount;
    bool running, endTime, playerControlOff;
    FriendlyWroom* friendlyCars;
    UberWroom* uberCars;
    Wroom* cars;
    Obstacle obstacles;
    Zabuszek zabuszek;
    clock_t lastCarMove, lastMoveTime, startTime, lastCarSpawn, lastFriendlySpawn;
    float time, elapsedTime;
    initializeLevelOne(HEIGHT, WIDTH, carSpeed, carAmount, gameTime, statusHeight, yCheck,
        moveCounter, wroomCount, delay, obstacleCount, maxWroomCount, friendlyWroomCount,
        uberCount, running, endTime, playerControlOff, friendlyCars, uberCars, cars,
        obstacles, zabuszek, lastCarMove, lastMoveTime, startTime, lastCarSpawn,
        lastFriendlySpawn, time, elapsedTime);
    handleLevelOneEnd(HEIGHT, WIDTH, running, endTime, carSpeed, carAmount, time, cars,
        friendlyCars, uberCars);
}
#endif
