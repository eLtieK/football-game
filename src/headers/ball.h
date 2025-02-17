#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "loader.h"
#include "physic.h"
#include <iostream>

class Ball {
public:
    void init(int x, int y);
    void move(float dt);
    void draw(SDL_Renderer* renderer);
    void applyForce(float fx, float fy);

private:
    int x, y, size = 20;
    float dx = 500.0f, dy = 0.0f; 
};

#endif
