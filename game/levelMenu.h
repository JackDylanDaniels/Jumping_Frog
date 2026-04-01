#ifndef levelMenu_H
#define levelMenu_H
#include <curses.h>
void gameStartLevelOne(int HEIGHT, int WIDTH, int carSpeed, int carAmount, float gameTime);
void gameStartLevelTwo(int HEIGHT, int WIDTH, int carSpeed, int carAmount, float gameTime);
void gameStartLevelThree(int HEIGHT, int WIDTH, int carSpeed, int carAmount);
void levelMenu(int HEIGHT, int WIDTH, int carSpeed, int carAmount, float gameTime) {
    const char* levels[] = { "---> Level 1", "---> Level 2", "---> Level 3" 
};
    int option = 0, n = 3;
    bool inLevelMenu = true;
    while (inLevelMenu) {
        clear();
        mvprintw((HEIGHT / 2) - 5, (WIDTH - 26) / 2, "-=- WYBIERZ LEVEL -=-");
        mvprintw(HEIGHT - 5, (WIDTH / 2) - strlen("Nacisnij 'esc' aby wrocic do glownego menu")/2, "Nacisnij 'esc' aby wrocic do glownego menu");
        for (int i = 0; i < n; i++) {
            if (i == option) {
                attron(A_REVERSE);
            
}
            mvprintw((HEIGHT / 2) + i, (WIDTH - 18) / 2, "%s", levels[i]);
            if (i == option) {
                attroff(A_REVERSE);
            
}
        
}
        int input = getch();
        switch (input) {
        case 'w': case 'W': case KEY_UP:
            option = (option + n - 1) % n;
            break;
        case 's': case 'S': case KEY_DOWN:
            option = (option + 1) % n;
            break;
        case 27:
            inLevelMenu = false;
            break;
        case '\n': case ' ':
            switch (option) {
            case 0:
                clear();
                gameStartLevelOne(HEIGHT, WIDTH, carSpeed, carAmount, gameTime);
                break;
            case 1:
                clear();
                gameStartLevelTwo(HEIGHT, WIDTH, carSpeed, carAmount, gameTime);
                break;
            case 2:
                clear();
                gameStartLevelThree(HEIGHT, WIDTH, carSpeed, carAmount);
                break;
            
}
            break;
        
}
    
}
}

#endif
