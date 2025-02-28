#ifndef LOGIC_H
#define LOGIC_H

#include "ui.h"

class GameLogic {
public:
    ~GameLogic();
    void init(SDL_Renderer* renderer);
    void draw();
    void setRenderer(SDL_Renderer * renderer);
    void resetScore() {this->score_p1 = 0; this->score_p2 = 0;};
    void addScore(int score, std::string team);

private:
    int score_p1 = 0;
    int score_p2 = 0;

    UiText* score_p1_text;
    UiText* score_p2_text;

    SDL_Renderer * renderer;
};

#endif