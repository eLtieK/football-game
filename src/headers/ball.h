#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "loader.h"

class Ball {
public:
    void init(int x, int y);
    void move(float dt);
    void draw(SDL_Renderer* renderer);

private:
    int x, y, dx = 1000, dy = 1000, size = 20;
};

#endif
