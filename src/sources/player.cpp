#include "../headers/player.h"

void Player::init(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::update(float dt) {
    move(dt);
    checkCollisionAndReset();
}

void Player::checkCollisionAndReset() {
    Uint32 currentTime = SDL_GetTicks(); 
    if (currentTime - lastCollisionTime >= resetInterval) {
        lastCollisionTime = currentTime;
        isCollision = false;
    }
}

void Player::move(float dt) {
    int dx = 0;

    // left and right
    if (direction_left) {dx = -1;}
    if (direction_right) {dx = 1;}
    if (direction_right && direction_left) {dx = 0;}
    x += dx * speed * dt;
    
    // jump
    if (isJumping) {
        velocityY += GRAVITY * dt;
        y += velocityY * dt;
    }

    // reset jump
    if (y >= GROUND - height) {
        y = GROUND - height;
        isJumping = false;
        velocityY = 0;
    }

    handlePlayerCollision(x, y, width, height);
}

void Player::setDirection(std::string dir, bool isMove) {
    if (dir == "left") direction_left = isMove;
    if (dir == "right") direction_right = isMove;
}

void Player::jump() {
    if (!isJumping) { 
        isJumping = true;
        velocityY = JUMP_VELOCITY;
    }
}

void Player::draw(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
