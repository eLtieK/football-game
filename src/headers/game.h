#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "ball.h"
#include "goal.h"
#include "sprite.h"
#include "ui.h"
#include "logic.h"

class Game {
public:
    void init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void updateClock();
    void render();
    void clean();
    bool running() { return isRunning; }

    // setter
    void setIsRunning(bool isRunning) {this->isRunning = isRunning;};
    void setIsPause(bool isPause) {this->isPause = isPause;};
    void setIsAi(bool isAi) {this->isAi = isAi;};
    void setDeltaTime(Uint32 &lastTime);
    void setStartTime() {this->startTime = SDL_GetTicks();};

    // getter
    SDL_Renderer * getRenderer() {return renderer;};
    float getDeltaTime();

    void loadBackground(const char* path);
    void restartScreen();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;

    bool isRunning;
    bool isPause = false;
    bool isAi = false;
    Player *player1;
    Player *player2;
    Ball ball;
    Goal *goalLeft;
    Goal *goalRight;
    int score1, score2;
    float deltaTime;
    AnimationSprite *smoke;

    //Ui
    UiText* game_clock;
    int startTime = 0;
    int currentTime = 60;
    int maxTime = 60;
    GameLogic uiLogic;
    GameOver gameOverScreen;
    WindUi wind;
};

#endif
