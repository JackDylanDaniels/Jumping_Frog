#ifndef checkCollisions_H
#define checkCollisions_H
bool checkCollisions(Zabuszek zabuszek, const int wroomCount, Wroom cars[], int HEIGHT, int WIDTH, bool playerControlOff) {
    if (playerControlOff) return false;
    for (int i = 0; i < wroomCount; i++) {
        if (zabuszek.x < cars[i].x + carWidth &&
            zabuszek.x + frogWidth > cars[i].x &&
            zabuszek.y < cars[i].y + carHeight &&
            zabuszek.y + frogHeight > cars[i].y) {
            return true;
        
}
    
}
    return false;
}
#endif
