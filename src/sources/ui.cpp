#include "../headers/game.h"
#include "../headers/ui.h"

const char * INTRO_PATH = "assests/images/background/intro.png";

bool Ui::isIntro = true; 
void Ui::init() {
    this->playerText = new UiText();
    this->playerText->setRenderer(renderer);
    this->playerText->init("PRESS 1 - PLAY",{255, 165, 0,255}, 50);
    this->playerText->setPosition(WINDOW_WIDTH / 2, 8 * WINDOW_HEIGHT / 10 - 60);
    this->playerText->setIsOutline(true);
    
    this->aiText = new UiText();
    this->aiText->setRenderer(renderer);
    this->aiText->init("PRESS 2 - BOT",{0, 191, 255,255}, 50);
    this->aiText->setPosition(WINDOW_WIDTH / 2, 8 * WINDOW_HEIGHT / 10);
    this->aiText->setIsOutline(true);

    loadBackground(INTRO_PATH);
}

Ui::~Ui() {
    delete playerText;
    delete aiText;
}

void Ui::handleEvents(Game &game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game.setIsRunning(false);
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1) {
            isIntro = false;
            game.setIsAi(false);
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_2) {
            isIntro = false;
            game.setIsAi(true);
        }
    }
}

void Ui::loadBackground(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Can't load %s: %s", path, IMG_GetError());
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!backgroundTexture) {
        SDL_Log("Can't create texture: %s", SDL_GetError());
    }
} 

void Ui::update() {
    
}

void Ui::render() {
    // Xóa màn hình
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu nền đen
    SDL_RenderClear(renderer);

    //background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    this->playerText->draw();
    this->aiText->draw();

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}

UiText::~UiText() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    TTF_CloseFont(font);
    TTF_Quit();
}

void UiText::init(const std::string& text, SDL_Color color, int font_size){
    name = text;
    textColor = color;

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", font_size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    textTexture = createTextTexture(text, color, 0);
    outlineTexture = createTextTexture(text, {0,0,0,255}, 1);
}

SDL_Texture* UiText::createTextTexture(const std::string& text, SDL_Color color, int outline) {
    TTF_SetFontOutline(font, outline);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Text Surface Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }

    rect.w = surface->w;
    rect.h = surface->h;
    SDL_FreeSurface(surface);
    return texture;
}

void UiText::setPosition(int x, int y) {
    rect.x = x - rect.w / 2; // Căn giữa theo chiều ngang
    rect.y = y - rect.h - 10; // Đặt phía trên nhân vật
}

void UiText::draw() {
    if (textTexture) {
        SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    }

    if (outlineTexture && isOutline) {
        SDL_RenderCopy(renderer, outlineTexture, NULL, &rect);
    }
}