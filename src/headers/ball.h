#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "loader.h"
#include "physic.h"
#include <iostream>
#include <algorithm>  

class Ball {
public:
    void init(int x, int y);
    void move(float dt);
    void update(float dt);
    void draw(SDL_Renderer* renderer);
    void applyForce(float fx, float fy);

    void loadBallTexture(const char* path, SDL_Renderer* renderer);

    // getter
    int getX() {return x;};
    int getY() {return y;};
    int getSize() {return size;};
    float getDx() {return dx;};
    float getDy() {return y;};

    // setter
    void setX(int x) {this->x = x;};
    void setY(int y) {this->y = y;};
    void setSize(int size) {this->size = size;};
    void setDx(float dx) {this->dx = dx;};
    void setDy(float dy) {this->dy = dy;};


private:
    int x, y, size = 80;
    float dx = 0.0f, dy = 0.0f; 
    SDL_Texture* ballTexture;
};

#endif
