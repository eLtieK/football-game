#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "loader.h"
#include "physic.h"
#include "ui.h"

#include <iostream>
#include <string>
#include <cstring>

const int OFFSET_HEAD_FRONT = 20;
const int OFFSET_HEAD_NAME = 40;
const int OFFSET_SHOE_BOT = 50;
const int OFFSET_HEAD_SHOE = 120;
const int SHOE_FRAMES = 10;

enum AnimationState {
    RUN,
    JUMP
};

class Player {
public:
    void init(int x, int y, bool isPlayer1, SDL_Renderer* renderer);
    void move(float dt);
    void jump();
    void update(float dt);
    void updateAI(int ballX, int ballY, std::string team);
    void updateShoeAnimation();
    void draw(SDL_Renderer* renderer);
    void setDirection(std::string dir, bool isMove);
    void checkCollisionAndReset();

    void loadHeadTexture(const char* path, SDL_Renderer* renderer);
    void loadShoeRunTexture(const char* path, SDL_Renderer* renderer);
    void loadShoeJumpTexture(const char* path, SDL_Renderer* renderer);

    // getter
    int getX() {return x;};
    int getY() {return y;};
    // int getHeight() {return h_height + s_height;};
    int getRealHeight() {return h_height + s_height - OFFSET_HEAD_SHOE - OFFSET_SHOE_BOT;};
    int getWidth() {return h_width;};
    bool getIsCollision() {return isCollision;};

    // setter
    void setIsCollision(bool isCollision) {
        this->isCollision = isCollision;
        lastCollisionTime = SDL_GetTicks();
    };

    //animation
    void setStandAnimation() {
        if (player_state == RUN) {this->frame_index = 0;} 
        else {this->updateShoeAnimation();}
    }
    void setPos(int x, int y) {this->x = x; this->y = y;}; 

protected:
    int x, y;
    int h_width = 180, h_height = 180;
    int s_width = 180, s_height = 180;
    int speed = 1400;
    int velocityY = 0; 
    bool isJumping = false;
    bool direction_left = false;
    bool direction_right = false;
    SDL_Texture* playerHeadTexture;
    SDL_Texture* playerShoeRunTexture[SHOE_FRAMES];
    SDL_Texture* playerShoeJumpTexture[SHOE_FRAMES];
    UiText* nametag;

    //timer
    bool isCollision = false;
    Uint32 lastCollisionTime = 0;
    const Uint32 resetInterval = 100; 

    //timer_shoe
    Uint32 lastFrameTime = 0;
    const int frame_delay = 50;
    int frame_index = 0;
    AnimationState player_state = RUN;
};

#endif
