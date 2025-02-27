#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "ball.h"
#include "goal.h"
#include "sprite.h"

class Game {
public:
    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }
    void setDeltaTime(Uint32 &lastTime);
    float getDeltaTime();

    // setter
    void setIsRunning(bool isRunning) {this->isRunning = isRunning;};

    // getter
    SDL_Renderer * getRenderer() {return renderer;};

    void loadBackground(const char* path);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;

    bool isRunning;
    Player *player1;
    Player *player2;
    Ball ball;
    Goal *goalLeft;
    Goal *goalRight;
    int score1, score2;
    float deltaTime;
    AnimationSprite *smoke;
};

#endif
