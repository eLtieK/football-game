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
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
        SDL_RenderFillRect(renderer, &rect);
    }
}
