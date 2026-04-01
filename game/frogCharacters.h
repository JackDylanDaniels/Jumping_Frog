#ifndef frogCharacters_H
#define frogCharacters_H
#include <curses.h>
void frogDirection(const char direction, const char*** s, int* height) {
        static const char* frogUp[] = {
                "* *",
                "---",
                "^*^"
        
};
        static const char* frogLeft[] = {
                "*|<",
                " |*",
                "*|<"
        
};
        static const char* frogRight[] = {
                ">|*",
                "*| ",
                ">|*"
        
};
        static const char* frogDown[] = {
                "v*v",
                "---",
                "* *"
        
};
        switch (direction) {
        case 'w':
                *s = frogUp;
                *height = 3;
                break;
        case 'a':
                *s = frogLeft;
                *height = 3;
                break;
        case 's':
                *s = frogDown;
                *height = 3;
                break;
        case 'd':
                *s = frogRight;
                *height = 3;
                break;
        default:
                *s = nullptr;
                *height = 0;
                break;
        
}
}
#endif
