#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "player.h"
#include "ball.h"

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

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    Player *player1;
    Player *player2;
    Ball ball;
    int score1, score2;
    float deltaTime;
};

#endif
