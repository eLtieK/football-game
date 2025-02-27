#include "../headers/game.h"
#include "../headers/ui.h"

void Ui::init() {
    // Khởi tạo SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }

    // Load font
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 30);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    // Tạo texture từ chữ
    textTexture = createTextTexture("Press ENTER to Start", {255, 255, 255});
}

Ui::~Ui() {
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();
}

SDL_Texture* Ui::createTextTexture(const std::string& text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Text Surface Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }
    textRect = {(WINDOW_WIDTH - surface->w )/ 2 , (WINDOW_HEIGHT - surface->h )/ 2, surface->w, surface->h};
    SDL_FreeSurface(surface);
    return texture;
}

void Ui::handleEvents(Game &game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game.setIsRunning(false);
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
            isIntro = false;
        }
    }
}

void Ui::update() {
    
}

void Ui::render() {
    // Xóa màn hình
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Màu nền đen
    SDL_RenderClear(renderer);

    // Vẽ chữ "Press ENTER to Start"
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

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
    outlineTexture = createTextTexture(text, {0,0,0,255}, 2);
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