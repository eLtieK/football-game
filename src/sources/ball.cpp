#include "../headers/ball.h"

void Ball::init(int x, int y) {
    this->x = x;
    this->y = y;
}

void Ball::update(float dt) {
    move(dt);
}

Ball::~Ball() {
    if (ballTexture) {
        SDL_DestroyTexture(ballTexture);
        ballTexture = nullptr;
    }
}

void Ball::move(float dt) {
    // van toc luc roi
    dy += GRAVITY * dt; 
    // van toc co ma sat
    dx *= FRICTION;
    // std::cout << dx << " " << dy << std::endl;

    if (dx < 0) { dx = std::max(-MAX_BALL_H_SPEED, dx);} 
    else {dx = std::min(MAX_BALL_H_SPEED, dx);}

    if (dy < 0) { dy = std::max(-MAX_BALL_V_SPEED, dy);} 
    else {dy = std::min(MAX_BALL_V_SPEED, dy);}

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
    // SDL_Rect rect = {x, y, size, size};
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(renderer, &rect);
    if (ballTexture) {
        SDL_Rect rect = {x, y , size, size}; // Vị trí và kích thước vẽ ảnh
        SDL_RenderCopy(renderer, ballTexture, NULL, &rect);
    } else {
        SDL_Log("Texture is null, can't render player.");
    }
}

void Ball::loadBallTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Can't load %s: %s", path, IMG_GetError());
    }
    
    ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FreeSurface(surface);
    if (!ballTexture) {
        SDL_Log("Can't create texture: %s", SDL_GetError());
    }
}