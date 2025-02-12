#include "src/headers/player.h"

void Player::init(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::move(int dx, int dy) {
    x += dx;
    y += dy;
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
