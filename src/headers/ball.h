#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

class Ball {
public:
    void init(int x, int y);
    void move();
    void draw(SDL_Renderer* renderer);

private:
    int x, y, dx = 4, dy = 4, size = 20;
};

#endif
