#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "loader.h"

#include <iostream>
#include <string>
#include <cstring>

class AnimationSprite {
public:
    void init(int size, int height, int frames, int frame_delay);
    ~AnimationSprite();
    void update(float dt);
    void updateAnimation();
    void draw(SDL_Renderer* renderer);

    void loadTexture(const char* path, SDL_Renderer* renderer);

    void setVisible(bool isVisible) {
        this->visible = isVisible;
        if (!isVisible) {frame_index = 0;}
        else {lastFrameTime = SDL_GetTicks();}
    };

    void setPos(int x, int y);

protected:
    int width, height;
    SDL_Rect rect;
    SDL_Texture** texture;
    bool visible = false;

    //timer
    Uint32 lastFrameTime = 0;
    int frame_delay = 0;
    int frame_index = 0;
    int frames = 0;
};

#endif
