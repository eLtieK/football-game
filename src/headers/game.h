#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "src/headers/player.h"
#include "src/headers/ball.h"

class Game {
public:
    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    Player player1, player2;
    Ball ball;
    int score1, score2;
};

#endif
