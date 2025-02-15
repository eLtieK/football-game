#include "../headers/ball.h"

void Ball::init(int x, int y) {
    this->x = x;
    this->y = y;
}

void Ball::move(float dt) {
    x += dx * dt;
    y += dy * dt;

    // Va chạm với biên trên và dưới
    if (y <= 0 || y >= WINDOW_HEIGHT - size) dy = -dy;

    // Va chạm với biên trái và phải (reset game)
    if (x <= 0 || x >= WINDOW_WIDTH - size) {
        dx = -dx;
    }
}

void Ball::draw(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, size, size};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
