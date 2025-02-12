#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
public:
    void init(int x, int y);
    void move(int dx, int dy);
    void jump();
    void draw(SDL_Renderer* renderer);

private:
    int x, y, width = 50, height = 50;
    int velocityY = 0; 
    bool isJumping = false;
};

#endif
