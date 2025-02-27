#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "loader.h"
#include <string>

class Game;

class Ui {
public:
    ~Ui();
    void init();
    void handleEvents(Game &game);
    void update();
    void render();
    SDL_Texture* createTextTexture(const std::string& text, SDL_Color color);
    
    // getter
    bool getIsIntro() {return isIntro;};

    // setter
    void setIsIntro(bool isIntro) {this->isIntro = isIntro;};
    void setRenderer(SDL_Renderer * renderer) {this->renderer = renderer;};

private:
    bool isIntro = true;
    SDL_Renderer* renderer;

    TTF_Font* font;
    SDL_Texture* textTexture;
    SDL_Rect textRect;
};

class UiText {
public:
    ~UiText();

    void init(const std::string& text, SDL_Color color, int font_size);
    void setRenderer(SDL_Renderer* renderer) {this->renderer = renderer;};
    void setPosition(int x, int y);
    void draw();
    SDL_Texture* createTextTexture(const std::string& text, SDL_Color color, int outline);

    //setter
    void setName(std::string name) {
        this->name = name;
        textTexture = createTextTexture(name, textColor, 0);
        outlineTexture = createTextTexture(name, {0,0,0,255}, 1);
    };

    void setIsPlayer1(bool isPlayer1) {this->isPlayer1 = isPlayer1;};
    void setIsOutline(bool isOutline) {this->isOutline = isOutline;};
    //getter
    bool getIsPlayer1() {return this->isPlayer1;};

private:
    std::string name;
    SDL_Texture* textTexture;
    SDL_Texture* outlineTexture;
    SDL_Renderer* renderer;
    SDL_Rect rect;
    TTF_Font* font;
    SDL_Color textColor = {255, 255, 255, 255}; // Mặc định màu trắng
    bool isPlayer1;
    bool isOutline = false;
};

#endif
