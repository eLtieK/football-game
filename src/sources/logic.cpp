#include "../headers/logic.h"

void GameLogic::init(SDL_Renderer* renderer) {
    this->score_p1_text = new UiText();
    this->score_p2_text = new UiText();
    this->setRenderer(renderer);

    this->score_p1_text->init(std::to_string(0), {0,175,255,255}, 80);
    this->score_p1_text->setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 6);
    this->score_p1_text->setIsOutline(true);

    this->score_p2_text->init(std::to_string(0), {255,128,0,255}, 80);
    this->score_p2_text->setPosition(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 6);
    this->score_p2_text->setIsOutline(true);
}

GameLogic::~GameLogic() {
    delete score_p1_text;
    delete score_p2_text;
}

void GameLogic::draw() {
    this->score_p1_text->draw();
    this->score_p2_text->draw();
}

void GameLogic::setRenderer(SDL_Renderer * renderer) {
    this->renderer = renderer;
    this->score_p1_text->setRenderer(renderer);
    this->score_p2_text->setRenderer(renderer);
}

void GameLogic::addScore(int score, std::string team) {
    if (team == "player1") {
        this->score_p1 += score;
        this->score_p1_text->setName(std::to_string(this->score_p1));
    }
    else if (team == "player2") {
        this->score_p2 += score;
        this->score_p2_text->setName(std::to_string(this->score_p2));
    }
}