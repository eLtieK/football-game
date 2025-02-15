#include "../headers/game.h"
#include "../headers/loader.h"
#include <iostream>

void Game::init(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    isRunning = true;
    
    player1.init(WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2);
    player2.init(WINDOW_WIDTH / 2 + 400, WINDOW_HEIGHT / 2);
    ball.init(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) isRunning = false;
        //handleInput(event, player1, player2);
    }
}

void Game::update() {
    ball.move(getDeltaTime());
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player1.draw(renderer);
    player2.draw(renderer);
    ball.draw(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::setDeltaTime(Uint32 &lastTime) {
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;  // Đổi từ ms sang giây
    lastTime = currentTime;
}

float Game::getDeltaTime() {
    return deltaTime;
}
