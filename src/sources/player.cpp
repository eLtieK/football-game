#include "../headers/player.h"
#include <iostream>

void Player::init(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::move(float dt) {
    int dx = 0;
    int dy = 0;
    if (direction_left) {dx = -1; dy = 0;}
    if (direction_right) {dx = 1; dy = 0;}
    if (direction_right && direction_left) {dx = 0; dy = 0;}
    x += dx * speed * dt;
    y += dy * speed * dt;
}

void Player::setDirection(std::string dir, bool isMove) {
    if (dir == "left") direction_left = isMove;
    if (dir == "right") direction_right = isMove;
}

void Player::jump() {
    if (!isJumping) {
        velocityY = -15;
        isJumping = true;
    }
}

void Player::draw(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
