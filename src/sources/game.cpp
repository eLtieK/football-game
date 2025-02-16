#include "../headers/game.h"
#include "../headers/loader.h"
#include <iostream>

void Game::init(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    isRunning = true;
    
    player1 = new Player();
    player2 = new Player();

    player1->init(WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2);
    player2->init(WINDOW_WIDTH / 2 + 400, WINDOW_HEIGHT / 2);
    ball.init(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) isRunning = false;
        SDL_Scancode key = event.key.keysym.scancode;
        if (event.type == SDL_KEYDOWN) {
            if (key == SDL_SCANCODE_A) {
                player1->setDirection("left", true);
            } if (key == SDL_SCANCODE_D) {
                player1->setDirection("right", true);
            } if (key == SDL_SCANCODE_LEFT) {
                player2->setDirection("left", true);
            } if (key == SDL_SCANCODE_RIGHT) {
                player2->setDirection("right", true);
            }
        } if (event.type == SDL_KEYUP) {
            if (key == SDL_SCANCODE_A) {
                player1->setDirection("left", false);
            } if (key == SDL_SCANCODE_D) {
                player1->setDirection("right", false);
            } if (key == SDL_SCANCODE_LEFT) {
                player2->setDirection("left", false);
            } if (key == SDL_SCANCODE_RIGHT) {
                player2->setDirection("right", false);
            }
        }
    }
}

void Game::update() {
    ball.move(deltaTime);
    player1->move(deltaTime);
    player2->move(deltaTime);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player1->draw(renderer);
    player2->draw(renderer);
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
