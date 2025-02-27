#include "../headers/goal.h"

void Goal::init(int x, int y) {
    rect = {x, y, this->width, this->height};
    texture = nullptr;
}

Goal::~Goal() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Goal::loadGoalTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Failed to load goal texture: %s", IMG_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Goal::draw(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
         // Vẽ viền cho khung thành
    } else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu đỏ (R,G,B,A)
    SDL_RenderDrawRect(renderer, &rect);
}

void Goal::setColor(Uint8 r, Uint8 g, Uint8 b) {
    color = {r, g, b, 255}; 
}
