#include "../headers/ball.h"

void Ball::init(int x, int y) {
    this->x = x;
    this->y = y;
}

void Ball::update(float dt) {
    move(dt);
}

void Ball::move(float dt) {
    // van toc luc roi
    dy += GRAVITY * dt; 
    // van toc co ma sat
    dx *= FRICTION;

    x += dx * dt;
    y += dy * dt;

    // Va chạm với biên trên và dưới
    handleBallCollision(x, y, dx, dy, size);
}

void Ball::applyForce(float fx, float fy) {
    dx += fx;
    dy += fy;
}

void Ball::draw(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, size, size};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
