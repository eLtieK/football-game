#include "../headers/sprite.h"

void AnimationSprite::init(int width, int height, int frames, int frame_delay) {
    this->width = width;
    this->height = height;
    this->frames = frames;
    this->frame_delay = frame_delay;
    texture = new SDL_Texture*[frames]();
}

void AnimationSprite::setPos(int x, int y) {
    rect = {x, y, this->width, this->height};
}

AnimationSprite::~AnimationSprite() {
    if (texture) {
        for (int i = 0; i < frames; i++) {
            if (texture[i]) {
                SDL_DestroyTexture(texture[i]);
                texture[i] = nullptr;
            }
        }
        delete[] texture;
        texture = nullptr;
    }
}

void AnimationSprite::updateAnimation() {
    Uint32 now = SDL_GetTicks();
    if(now - lastFrameTime >= frame_delay) {
        frame_index = (frame_index + 1);
        lastFrameTime = now;
    }
}

void AnimationSprite::update(float dt) {
    if (visible) {
        updateAnimation();
        if (frame_index >= frames) {
            setVisible(false);
        }
    }
}

void AnimationSprite::loadTexture(const char* path, SDL_Renderer* renderer) {
    for (int i = 0; i < frames; i++) {
        std::string filePath = std::string(path) + "/" + std::to_string(i + 1) + ".png"; 
        SDL_Surface* surface = IMG_Load(filePath.c_str());

        if (!surface) {
            SDL_Log("Failed to load %s: %s", filePath.c_str(), SDL_GetError());
            continue;
        }

        texture[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void AnimationSprite::draw(SDL_Renderer* renderer) {
    if (texture) {
        if (visible) {SDL_RenderCopy(renderer, texture[frame_index], NULL, &rect);}
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
        SDL_RenderFillRect(renderer, &rect);
    }
}
