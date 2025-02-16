#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <string>

class Player {
public:
    void init(int x, int y);
    void move(float dt);
    void jump();
    void draw(SDL_Renderer* renderer);
    void setDirection(std::string dir, bool isMove);

protected:
    int x, y, width = 50, height = 50;
    int speed = 1000;
    int velocityY = 0; 
    bool isJumping = false;
    bool direction_left = false;
    bool direction_right = false;
};

#endif
