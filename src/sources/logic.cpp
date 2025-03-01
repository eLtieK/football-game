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

void GameLogic::resetScore() {
    this->score_p1 = 0;
    this->score_p1_text->setName(std::to_string(this->score_p1));
    this->score_p2 = 0;
    this->score_p2_text->setName(std::to_string(this->score_p1));
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

std::string GameLogic::getPlayerWin() {
    if (this->score_p1 > this->score_p2) return "PLAYER 1 WINS!";
    else if (this->score_p1 < this->score_p2) return "PLAYER 2 WINS!";
    else return "TIE!";
}

GameOver::~GameOver() {
    delete GameOverText;
    delete PlayAgainText;
    delete MainMenuText;
    delete QuitText;
}

void GameOver::init(SDL_Renderer* renderer) {
    GameOverText = new UiText();
    PlayAgainText = new UiText();
    MainMenuText = new UiText();
    QuitText = new UiText();
    this->setRenderer(renderer);

    GameOverText->init("Game Over", {255, 0, 0, 255}, 100);
    GameOverText->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 50);
    GameOverText->setIsOutline(true);

    PlayAgainText->init("Play Again", {255, 255, 255, 255}, 50);
    PlayAgainText->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    PlayAgainText->setIsOutline(true);
    
    MainMenuText->init("Main Menu", {255, 255, 255, 255}, 50);
    MainMenuText->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 80);
    MainMenuText->setIsOutline(true);
    
    QuitText->init("Quit", {255, 255, 255, 255}, 50);
    QuitText->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 160);
    QuitText->setIsOutline(true);
}

std::string GameOver::update() {
    if (this->playAgain() != "") {return this->playAgain();}
    if (this->mainMenu() != "") {return this->mainMenu();}
    if (this->quit() != "") {return this->quit();}
    return "";
}

void GameOver::draw() {
    GameOverText->draw();
    PlayAgainText->draw();
    MainMenuText->draw();
    QuitText->draw();
}

void GameOver::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
    GameOverText->setRenderer(renderer);
    PlayAgainText->setRenderer(renderer);
    MainMenuText->setRenderer(renderer);
    QuitText->setRenderer(renderer);
}

void GameOver::setGameover(std::string str) {
    GameOverText->setName(str);
    GameOverText->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 50);
}

std::string GameOver::playAgain() {
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) return "";

    int posX = PlayAgainText->getRect().x;
    int posY = PlayAgainText->getRect().y;
    int width = PlayAgainText->getRect().w;
    int height = PlayAgainText->getRect().h;

    if(mouseX < posX || mouseX > posX + width) return "";
    if(mouseY < posY || mouseY > posY + height) return "";

    return "playAgain";
} 

std::string GameOver::mainMenu() {
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) return "";

    int posX = MainMenuText->getRect().x;
    int posY = MainMenuText->getRect().y;
    int width = MainMenuText->getRect().w;
    int height = MainMenuText->getRect().h;

    if(mouseX < posX || mouseX > posX + width) return "";
    if(mouseY < posY || mouseY > posY + height) return "";

    return "mainMenu";
}

std::string GameOver::quit() {    
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) return "";

    int posX = QuitText->getRect().x;
    int posY = QuitText->getRect().y;
    int width = QuitText->getRect().w;
    int height = QuitText->getRect().h;

    if(mouseX < posX || mouseX > posX + width) return "";
    if(mouseY < posY || mouseY > posY + height) return "";

    return "quit";
}
