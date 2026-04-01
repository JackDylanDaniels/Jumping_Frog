#ifndef fileRead_H
#define fileRead_H
#include <stdio.h>
#include <cstring>
void fileRead(const char *name, int* carSpeed, int* carAmount, float* time, int* obstacleAmount) {
        FILE* file = fopen("gameParameters.txt", "r");
        if (file == NULL) return;
        char fileInput[20];
        float tempTime;
    while (fscanf(file, "%s", fileInput) != EOF) {
        if (strcmp(fileInput, "CAR_SPEED") == 0 && carSpeed != nullptr) {
            fscanf(file, "%d", carSpeed);
        
}
        else if (strcmp(fileInput, "CAR_AMOUNT") == 0 && carAmount != nullptr) {
            fscanf(file, "%d", carAmount);
        
}
        else if (strcmp(fileInput, "TIME") == 0) {
            if (time != nullptr) {
                fscanf(file, "%f", time);
            
}
            else {
                fscanf(file, "%f", &tempTime);
            
}
        
}
        else if (strcmp(fileInput, "OBSTACLE_AMOUNT") == 0 && obstacleAmount != nullptr) {
            fscanf(file, "%d", obstacleAmount);
        
}
    
}
        fclose(file);
}
#endif 
