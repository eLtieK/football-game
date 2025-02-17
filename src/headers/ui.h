#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

#endif
