#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "loader.h"
#include "physic.h"

#include <iostream>
#include <string>

class Player {
public:
    void init(int x, int y);
    void move(float dt);
    void jump();
    void update(float dt);
    void draw(SDL_Renderer* renderer);
    void setDirection(std::string dir, bool isMove);
    void checkCollisionAndReset();

    // getter
    int getX() {return x;};
    int getY() {return y;};
    int getHeight() {return height;};
    int getWidth() {return width;};
    bool getIsCollision() {return isCollision;};

    // setter
    void setIsCollision(bool isCollision) {
        this->isCollision = isCollision;
        lastCollisionTime = SDL_GetTicks();
    };

protected:
    int x, y, width = 100, height = 100;
    int speed = 1400;
    int velocityY = 0; 
    bool isJumping = false;
    bool direction_left = false;
    bool direction_right = false;

    //timer
    bool isCollision = false;
    Uint32 lastCollisionTime = 0;
    const Uint32 resetInterval = 100; 
};

#endif
