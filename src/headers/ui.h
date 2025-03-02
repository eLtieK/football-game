#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "loader.h"
#include <string>
#include "audio.h"
#include <random>  // Thư viện random hiện đại

class Game;
class Ball;

class UiText;

class Ui {
public:
    ~Ui();
    void init();
    void handleEvents(Game &game);
    void update();
    void render();
    void loadBackground(const char* path);
    
    // getter
    static bool getIsIntro() {return isIntro;};

    // setter
    static void setIsIntro(bool value) {Ui::isIntro = value;};
    void setRenderer(SDL_Renderer * renderer) {this->renderer = renderer;};

private:
    static bool isIntro;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;

    UiText * playerText;
    UiText * aiText;
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

        if(textTexture) {SDL_DestroyTexture(textTexture);} //xoa cai cu
        if(outlineTexture) {SDL_DestroyTexture(outlineTexture);}

        textTexture = createTextTexture(name, textColor, 0);
        outlineTexture = createTextTexture(name, {0,0,0,255}, 1);
    };

    void setIsPlayer1(bool isPlayer1) {this->isPlayer1 = isPlayer1;};
    void setIsOutline(bool isOutline) {this->isOutline = isOutline;};

    //getter
    bool getIsPlayer1() {return this->isPlayer1;};
    SDL_Rect getRect() {return this->rect;};

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

class WindUi : public UiText {
public:
    void init(SDL_Renderer * renderer);

    void randomDirect();
    void update(Ball &ball);
    void updateBall(Ball &ball);
    void draw();

private:
    bool visible = false;
    int direction;
    Uint32 lastWindTime = 0;    // Lưu thời gian sự kiện gió trước đó
    Uint32 windStartTime = 0;   // Lưu thời gian gió bắt đầu xuất hiện
    const Uint32 windCooldown = 5000;  // 5 giây giữa các lần gió
    const Uint32 windDuration = 3000;  // Gió tồn tại trong 3 giây
};
    

#endif
