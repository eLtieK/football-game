#ifndef LOGIC_H
#define LOGIC_H

#include "ui.h"
// #include <ostream>
#include <iostream>

class GameLogic {
public:
    ~GameLogic();
    void init(SDL_Renderer* renderer);
    void draw();
    void setRenderer(SDL_Renderer * renderer);
    void resetScore();
    void addScore(int score, std::string team);
    std::string getPlayerWin();

private:
    int score_p1 = 0;
    int score_p2 = 0;

    UiText* score_p1_text;
    UiText* score_p2_text;

    SDL_Renderer * renderer;
};

class GameOver {
public:
    ~GameOver();
    void init(SDL_Renderer* renderer);
    std::string update();
    void draw();

    std::string playAgain();
    std::string mainMenu();
    std::string quit();

    //setter
    void setRenderer(SDL_Renderer * renderer);
    void setGameover(std::string str);

private:
    UiText* GameOverText;
    UiText* PlayAgainText;
    UiText* MainMenuText;
    UiText* QuitText;

    SDL_Renderer * renderer;
};

#endif