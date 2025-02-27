#ifndef GOAL_H
#define GOAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Goal {
public:
    void init(int x, int y);
    ~Goal();

    void loadGoalTexture(const char* path, SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer);
    SDL_Rect getRect() { return rect; }

    //getter
    int getWidth() {return this->width;}
    int getHeight() {return this->height;}

    //setter
    void setColor(Uint8 r, Uint8 g, Uint8 b);

private:
    int width = 50, height = 200;
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Color color = {255, 255, 255, 255}; // Mặc định là màu trang
};

#endif
