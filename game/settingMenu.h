#ifndef settingMenu_H
#define settingMenu_H
#include "fileRead.h"
void settingMenu(int HEIGHT, int WIDTH) {
    clear();
    int carSpeed = 1, carAmount = 3, option = 0, obstacleAmount = 0;
    float time = 30.0;
    fileRead("gameParameters.txt", &carSpeed, &carAmount, &time, &obstacleAmount);
    mvprintw((HEIGHT / 2) - 5, (WIDTH - 26) / 2, "-=- USTAWIENIA -=-");
    mvprintw(HEIGHT - 5, (WIDTH / 2) - strlen("Nacisnij cokolwiek aby wrocic do glownego menu") / 2, "Nacisnij cokolwiek aby wrocic do glownego menu");
    mvprintw((HEIGHT / 2) - 3, (WIDTH - 42) / 2, "Ustawienia mozna zmienic w pliku 'gameParameters.txt'");
    mvprintw((HEIGHT / 2), (WIDTH - 36) / 2, "---> Predkosc samochodow (CAR_SPEED): %d", carSpeed);
    mvprintw((HEIGHT / 2) + 1, (WIDTH - 36) / 2, "---> Ilosc samochodow (CAR_AMOUNT): %d", carAmount);
    mvprintw((HEIGHT / 2) + 2, (WIDTH - 36) / 2, "---> Czas gry (TIME): %.1f", time);
    mvprintw((HEIGHT / 2) + 3, (WIDTH - 36) / 2, "---> Ilosc przeszkod (OBSTACLE_AMOUNT): %d", obstacleAmount);
    refresh();
    getch();
}
#endif
