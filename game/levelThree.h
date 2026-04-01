#ifndef levelThree_H
#define levelThree_H
#include "zabuszek.h"
void initWroom(Wroom cars[], int wroomCount, int HEIGHT, int WIDTH, int& carSpeed, int friendlyWroomCount);
Zabuszek initZabuszek(int HEIGHT, int WIDTH, int statusHeight);
void randWroomSpeed(Wroom& car, int& carSpeed);
void drawRoadsNoMeta(Zabuszek zabuszek, int HEIGHT, int WIDTH, int statusHeight);
void wroomCreater(Wroom cars[], int wroomCount, FriendlyWroom* friendlyCars, int friendlyWroomCount, UberWroom* uberCars, int uberCount, int HEIGHT, Zabuszek& zabuszek, bool& playerControlOff);
void wroomMover(Wroom cars[], FriendlyWroom* friendlyCars, UberWroom* uberCars, int friendlyWroomCount, int uberCount, int carCount, int WIDTH, Zabuszek& zabuszek, bool& playerControlOff);
void statusLevelThree(int HEIGHT, int WIDTH, Zabuszek& zabuszek, float& survivalTime, int& moveCounter);
void gsInput(int input, int HEIGHT, int WIDTH, bool& running, Zabuszek& zabuszek, int& yCheck, int& moveCounter, clock_t& lastMoveTime, Obstacle& obstacles, int& obstacleCount, bool& playerControlOff, UberWroom* uberCars, int uberCount, int level);
bool checkCollisions(Zabuszek zabuszek, const int wroomCount, Wroom cars[], int HEIGHT, int WIDTH, bool playerControlOff);
void initLevelThreeComponents(int HEIGHT, int WIDTH, int carSpeed, int carAmount, FriendlyWroom*& friendlyCars, UberWroom*& uberCars, Wroom*& cars, Zabuszek& zabuszek, Obstacle*& obstacles, Stork& stork, int& obstacleCount, int& friendlyWroomCount, int& uberCount, int& wroomCount, int statusHeight) {
    friendlyWroomCount = carAmount / 3;
    uberCount = carAmount / 3;
    wroomCount = carAmount * 2;
    friendlyCars = new FriendlyWroom[friendlyWroomCount];
    uberCars = new UberWroom[uberCount];
    cars = new Wroom[wroomCount];
    initFriendlyWroom(friendlyCars, friendlyWroomCount, HEIGHT, WIDTH, &carSpeed);
    initUberWroom(uberCars, uberCount, HEIGHT, WIDTH, &carSpeed);
    initStork(&stork, HEIGHT, WIDTH);
    initWroom(cars, wroomCount, HEIGHT, WIDTH, carSpeed);
    fileRead("gameParameters.txt", &carSpeed, &carAmount, nullptr, &obstacleCount);
    if (obstacleCount > 0) {
        obstacles = new Obstacle[obstacleCount];
        initObstacles(obstacles, obstacleCount, HEIGHT, WIDTH, statusHeight);
    
}
    zabuszek = initZabuszek(HEIGHT, WIDTH, statusHeight);
}
void levelThreeSpeedIncrease(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars,
    int wroomCount, int friendlyWroomCount, int uberCount,
    int carSpeed, int& speedMultiplier,
    clock_t& lastSpeedIncrease, clock_t currentTime) {  //Zwiększanie prędkości samochodów aby gra nie szła w nieskończoność
    double timeSinceSpeedIncrease = (double)(currentTime - lastSpeedIncrease) / CLOCKS_PER_SEC;
    if (timeSinceSpeedIncrease >= 10.0) {   //10s na zmianę prędkości
        speedMultiplier++;
        lastSpeedIncrease = currentTime;
        for (int i = 0; i < wroomCount; i++) {
            cars[i].speed = (rand() % (carSpeed + 2) + 1) * speedMultiplier;
        
}
        for (int i = 0; i < friendlyWroomCount; i++) {
            if (friendlyCars[i].isActive) {
                friendlyCars[i].speed = (rand() % (carSpeed + 2) + 1) * speedMultiplier;
            
}
        
}
        for (int i = 0; i < uberCount; i++) {
            uberCars[i].speed = (rand() % (carSpeed + 2) + 1) * speedMultiplier;
        
}
    
}
}
void levelThreeSpawnManagement(FriendlyWroom* friendlyCars, int friendlyWroomCount, int HEIGHT, int WIDTH, int carSpeed, clock_t& lastFriendlySpawn, const double spawnInterval, clock_t currentTime) { //Tworzenie nowych samochodów w ustalonym czasie
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
void handleLevelThreeEnd(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars, Obstacle* obstacles) {  //Koniec poziomu trzeciego
    delete[] cars;
    delete[] friendlyCars;
    delete[] uberCars;
    if (obstacles) {
        delete[] obstacles;
    
}
}
void initLevelThreeVariables(int& statusHeight, int& yCheck, int& moveCounter, int& wroomCount,
    int& delay, int& obstacleCount, int& friendlyWroomCount, int& uberCount, int& speedMultiplier,
    bool& running, bool& playerControlOff) {    //Zainicjowanie zmiennych
    statusHeight = 6;
    yCheck = 0;
    moveCounter = 0;
    delay = 200;
    obstacleCount = 0;
    speedMultiplier = 1;
    running = true;
    playerControlOff = false;
}

void handleLevelThreeLoopIF(int HEIGHT, int WIDTH, Wroom* cars, Stork& stork,
    bool& running, bool playerControlOff, int wroomCount, float survivalTime,
    int moveCounter, int carSpeed, int carAmount, Zabuszek& zabuszek) { //Koniec gry ekran dla końca gry
    if (checkCollisions(zabuszek, wroomCount, cars, HEIGHT, WIDTH, playerControlOff) ||
        checkStorkCollision(&stork, &zabuszek, playerControlOff)) {
        saveScore(survivalTime, moveCounter, 3);    //Zapisywanie danych do rankingu
        gameOverScreen(HEIGHT, WIDTH, survivalTime);
        nodelay(stdscr, FALSE);
        int input = getch();
        switch (input) {
        case 'r':
            clear();
            gameStartLevelThree(HEIGHT, WIDTH, carSpeed, carAmount);
            break;
        case 27:
            levelMenu(HEIGHT, WIDTH, carSpeed, carAmount, 0);
            break;
        
}
        running = false;
    
}
}

void handleLevelThreeDrawing(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars,
    Stork& stork, int HEIGHT, int WIDTH, int statusHeight, bool& playerControlOff,
    int wroomCount, int friendlyWroomCount, int uberCount, int obstacleCount,
    Obstacle* obstacles, Zabuszek& zabuszek, float survivalTime, int& moveCounter) {    //Rysowanie ekranu
    drawRoadsNoMeta(zabuszek, HEIGHT, WIDTH, statusHeight);
    wroomCreater(cars, wroomCount, friendlyCars, friendlyWroomCount, uberCars, uberCount,
        HEIGHT, zabuszek, playerControlOff);
    drawObstacles(obstacles, obstacleCount);
    drawStork(&stork);
    statusLevelThree(HEIGHT, WIDTH, zabuszek, survivalTime, moveCounter);
    refresh();
}
void handleLevelThreeLoopIFv2(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars,
    Stork& stork, int HEIGHT, int WIDTH, int statusHeight, bool& running,
    bool& playerControlOff, int wroomCount, int friendlyWroomCount, int uberCount,
    int& moveCounter, int& yCheck, int obstacleCount, Obstacle* obstacles,
    Zabuszek& zabuszek, int delay, int carSpeed, int carAmount, int& speedMultiplier,
    clock_t& lastCarMove, clock_t& lastMoveTime, clock_t& lastFriendlySpawn,
    clock_t& lastSpeedIncrease, clock_t startTime, clock_t currentTime, float survivalTime) {
    if ((double)(currentTime - lastCarMove) / CLOCKS_PER_SEC >= delay / 1000.0) {   //Ruszanie się samochodów i bociana 
        wroomMover(cars, friendlyCars, uberCars, friendlyWroomCount, uberCount, wroomCount,
            WIDTH, zabuszek, playerControlOff);
        moveStork(&stork, &zabuszek, playerControlOff);
        lastCarMove = currentTime;
    
}
    handleLevelThreeDrawing(cars, friendlyCars, uberCars, stork, HEIGHT, WIDTH, statusHeight,
        playerControlOff, wroomCount, friendlyWroomCount, uberCount, obstacleCount,
        obstacles, zabuszek, survivalTime, moveCounter);
    int input = getch();
    if (input != ERR) {
        gsInput(input, HEIGHT, WIDTH, running, zabuszek, yCheck, moveCounter, lastMoveTime,
            *obstacles, obstacleCount, playerControlOff, uberCars, uberCount, 3);
    
}
    handleLevelThreeLoopIF(HEIGHT, WIDTH, cars, stork, running, playerControlOff,
        wroomCount, survivalTime, moveCounter, carSpeed, carAmount, zabuszek);
}
void handleLevelThreeLoop(Wroom* cars, FriendlyWroom* friendlyCars, UberWroom* uberCars,
    Stork& stork, int HEIGHT, int WIDTH, int statusHeight, bool& running,
    bool& playerControlOff, int wroomCount, int friendlyWroomCount, int uberCount,
    int& moveCounter, int& yCheck, int obstacleCount, Obstacle* obstacles,
    Zabuszek& zabuszek, int delay, int carSpeed, int carAmount, int& speedMultiplier,
    clock_t& lastCarMove, clock_t& lastMoveTime, clock_t& lastFriendlySpawn,
    clock_t& lastSpeedIncrease, clock_t startTime) {    //Zwiększanie prędkości + zmiana ustawien samochodów
    clock_t currentTime = clock();
    float survivalTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC;
    levelThreeSpeedIncrease(cars, friendlyCars, uberCars, wroomCount, friendlyWroomCount,
        uberCount, carSpeed, speedMultiplier, lastSpeedIncrease, currentTime);
    levelThreeSpawnManagement(friendlyCars, friendlyWroomCount, HEIGHT, WIDTH, carSpeed,
        lastFriendlySpawn, 2.0, currentTime);
    handleLevelThreeLoopIFv2(cars, friendlyCars, uberCars, stork, HEIGHT, WIDTH, statusHeight, running, playerControlOff, wroomCount, friendlyWroomCount, uberCount, moveCounter, yCheck, obstacleCount, obstacles, zabuszek, delay, carSpeed, carAmount, speedMultiplier, lastCarMove, lastMoveTime, lastFriendlySpawn, lastSpeedIncrease, startTime, currentTime, survivalTime);
}
void initializeLevelThree(int HEIGHT, int WIDTH, int carSpeed, int carAmount,
    int& statusHeight, int& yCheck, int& moveCounter, int& wroomCount, int& delay,
    int& obstacleCount, int& friendlyWroomCount, int& uberCount, int& speedMultiplier,
    bool& running, bool& playerControlOff, FriendlyWroom*& friendlyCars,
    UberWroom*& uberCars, Wroom*& cars, Obstacle*& obstacles, Stork& stork,
    Zabuszek& zabuszek, clock_t& lastCarMove, clock_t& lastMoveTime,
    clock_t& startTime, clock_t& lastFriendlySpawn, clock_t& lastSpeedIncrease) {   //Zainicjować level
    initLevelThreeVariables(statusHeight, yCheck, moveCounter, wroomCount, delay,
        obstacleCount, friendlyWroomCount, uberCount, speedMultiplier,
        running, playerControlOff);
    initLevelThreeComponents(HEIGHT, WIDTH, carSpeed, carAmount, friendlyCars, uberCars,
        cars, zabuszek, obstacles, stork, obstacleCount, friendlyWroomCount,
        uberCount, wroomCount, statusHeight);
    lastCarMove = clock();
    lastMoveTime = clock();
    startTime = clock();
    lastFriendlySpawn = clock();
    lastSpeedIncrease = clock();
    nodelay(stdscr, TRUE);
    while (running) {
        handleLevelThreeLoop(cars, friendlyCars, uberCars, stork, HEIGHT, WIDTH, statusHeight,
            running, playerControlOff, wroomCount, friendlyWroomCount, uberCount, moveCounter,
            yCheck, obstacleCount, obstacles, zabuszek, delay, carSpeed, carAmount,
            speedMultiplier, lastCarMove, lastMoveTime, lastFriendlySpawn,
            lastSpeedIncrease, startTime);
    
}
}
void gameStartLevelThree(int HEIGHT, int WIDTH, int carSpeed, int carAmount) {  //Główny zainicjowania gry
    int statusHeight, yCheck, moveCounter, wroomCount, delay, obstacleCount,
        friendlyWroomCount, uberCount, speedMultiplier;
    bool running, playerControlOff;
    FriendlyWroom* friendlyCars;
    UberWroom* uberCars;
    Wroom* cars;
    Obstacle* obstacles = nullptr;
    Stork stork;
    Zabuszek zabuszek;
    clock_t lastCarMove, lastMoveTime, startTime, lastFriendlySpawn, lastSpeedIncrease;
    initializeLevelThree(HEIGHT, WIDTH, carSpeed, carAmount, statusHeight, yCheck,
        moveCounter, wroomCount, delay, obstacleCount, friendlyWroomCount, uberCount,
        speedMultiplier, running, playerControlOff, friendlyCars, uberCars, cars,
        obstacles, stork, zabuszek, lastCarMove, lastMoveTime, startTime,
        lastFriendlySpawn, lastSpeedIncrease);
    handleLevelThreeEnd(cars, friendlyCars, uberCars, obstacles);
}
#endif
