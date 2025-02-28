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
    void update();
    void draw(SDL_Renderer* renderer);
    SDL_Rect getRect() { return rect; }

    //getter
    int getWidth() {return this->width;}
    int getHeight() {return this->height;}
    bool getIsLeft() {return this->isLeft;};

    //setter
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void setIsLeft(bool isLeft) {this->isLeft = isLeft;};

    //timer
    void setGoal();

private:
    int width = 50, height = 200;
    bool isLeft = true;
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Color color = {255, 255, 255, 255}; // Mặc định là màu trang

    //timer
    bool isGreen = false;  
    Uint32 colorChangeTime = 0;
    int delay_time = 2000;
};

#endif
