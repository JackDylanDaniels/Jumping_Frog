#ifndef rankingSystem_H
#define rankingSystem_H
#include <stdio.h>
#include <curses.h>
#define TOP10 10
typedef struct {
    float score;
    int moves;
    float time;
} Ranking;
void saveScore(float time, int moves, int level) {  //Zapisywanie wyników
    Ranking newScore;
    newScore.time = time;
    newScore.moves = moves;
    newScore.score = (moves / time) * 100;  //Punktacja na podstawie czasu i ilości ruchów
    char filename[20];
    sprintf(filename, "ranks_level%d.dat", level);  //Plik z wynikami dla każdego levelu
    FILE* file = fopen(filename, "ab");
    if (file != NULL) {
        fwrite(&newScore, sizeof(Ranking), 1, file);
        fclose(file);
    
}
}
void showRankingForLevel(int HEIGHT, int WIDTH, int level) {    //Pokazanie wyników
    clear();
    char text[50];
    sprintf(text, "-=- TOP 10 NAJLEPSZYCH WYNIKOW - Level %d -=-", level);
    mvprintw((HEIGHT / 2) - 5, (WIDTH / 2) - strlen(text)/2, text);
    Ranking ranks[TOP10];
    int count = 0;
    char filename[20];
    sprintf(filename, "ranks_level%d.dat", level);
    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        Ranking temp;
        while (fread(&temp, sizeof(Ranking), 1, file) == 1 && count < TOP10) {
            ranks[count++] = temp;
        
}
        fclose(file);
    
}
    if (count == 0) {
        mvprintw(HEIGHT / 2, (WIDTH / 2) - strlen("Obecnie brak wynikow")/2, "Obecnie brak wynikow");
    
}
    for (int i = 0; i < count; i++) {   //Sortowanie bąbelkowe po to, aby sortować wyniki
        for (int j = 1; j < count-i; j++) {
            if (ranks[j-1].score < ranks[j].score) {
                Ranking temp = ranks[j];
                ranks[j] = ranks[j-1];
                ranks[j-1] = temp;
            
}
        
}
    
}
    for (int i = 0; i < count; i++) {
        mvprintw((HEIGHT / 2) - 3 + i, (WIDTH / 2) - 20, "%d.    Score: %.2f      Time: %.2f, Moves: %d", i + 1, ranks[i].score, ranks[i].time, ranks[i].moves);
    
}
    mvprintw(HEIGHT - 3, WIDTH / 2 - strlen("Nacisnij dowolny klawisz aby wrocic")/2, "Nacisnij dowolny klawisz aby wrocic");
    refresh();
    getch();
}
void rankingMenu(int HEIGHT, int WIDTH) {
    int option = 0;
    const int numOptions = 3;
    bool inMenu = true;
    while (inMenu) {
        clear();
        mvprintw(HEIGHT / 2 - 5, WIDTH / 2 - 10, "-=- WYBIERZ LEVEL -=-");
        const char* options[] = {
            "---> Ranking Level 1",
            "---> Ranking Level 2",
            "---> Ranking Level 3"
        
};
        for (int i = 0; i < numOptions; i++) {
            if (i == option) {
                attron(A_REVERSE);
            
}
            mvprintw(HEIGHT / 2 + i, WIDTH / 2 - strlen(options[i]) / 2, options[i]);
            if (i == option) {
                attroff(A_REVERSE);
            
}
        
}
        mvprintw(HEIGHT - 3, WIDTH / 2 - 15, "Nacisnij 'esc' aby wrocic do glownego menu");
        refresh();
        int input = getch();
        switch (input) {
        case 'w': case 'W': case KEY_UP:
            option = (option + numOptions - 1) % numOptions;
            break;
        case 's': case 'S': case KEY_DOWN:
            option = (option + 1) % numOptions;
            break;
        case 27:  // ESC
            inMenu = false;
            break;
        case '\n': case ' ':
            showRankingForLevel(HEIGHT, WIDTH, option + 1);
            break;
        
}
    
}
}
#endif
