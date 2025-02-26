#include "../headers/game.h"

const char * BACKGROUND_PATH = "assests/images/background/background2.jpg";
const char * PLAYER1_HEAD_PATH = "assests/images/head/head1/Picture49.png";
const char * PLAYER2_HEAD_PATH = "assests/images/head/head2/Picture50.png";
const char * PLAYER1_SHOE_RUN_PATH = "assests/images/shoe/shoe1/walk";
const char * PLAYER2_SHOE_RUN_PATH = "assests/images/shoe/shoe2/walk";
const char * PLAYER1_SHOE_JUMP_PATH = "assests/images/shoe/shoe1/jump";
const char * PLAYER2_SHOE_JUMP_PATH = "assests/images/shoe/shoe2/jump";
const char * BALL_PATH = "assests/images/ball/ball.png";

void Game::init(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_JPG);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    isRunning = true;
    
    player1 = new Player();
    player2 = new Player();

    player1->init(WINDOW_WIDTH / 2 - 400, GROUND - player1->getRealHeight(), true);
    player2->init(WINDOW_WIDTH / 2 + 400, GROUND - player2->getRealHeight(), false);
    ball.init(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    // load texture
    loadBackground(BACKGROUND_PATH);
    player1->loadHeadTexture(PLAYER1_HEAD_PATH, renderer);
    player2->loadHeadTexture(PLAYER2_HEAD_PATH, renderer);

    player1->loadShoeRunTexture(PLAYER1_SHOE_RUN_PATH, renderer);
    player2->loadShoeRunTexture(PLAYER2_SHOE_RUN_PATH, renderer);

    player1->loadShoeJumpTexture(PLAYER1_SHOE_JUMP_PATH, renderer);
    player2->loadShoeJumpTexture(PLAYER2_SHOE_JUMP_PATH, renderer);

    ball.loadBallTexture(BALL_PATH, renderer);
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) isRunning = false;
        SDL_Scancode key = event.key.keysym.scancode;
        if (event.type == SDL_KEYDOWN) {
            // player1
            if (key == SDL_SCANCODE_A) { player1->setDirection("left", true);} 
            if (key == SDL_SCANCODE_D) { player1->setDirection("right", true);}
            if (key == SDL_SCANCODE_W) { player1->jump(); }

            // player2
            if (key == SDL_SCANCODE_LEFT) { player2->setDirection("left", true);} 
            if (key == SDL_SCANCODE_RIGHT) { player2->setDirection("right", true);}
            if (key == SDL_SCANCODE_UP) { player2->jump(); }

            if (key == SDL_SCANCODE_SPACE) {ball.applyForce(3000, -1500);}

        } if (event.type == SDL_KEYUP) {
            if (key == SDL_SCANCODE_A) { player1->setDirection("left", false);} 
            if (key == SDL_SCANCODE_D) { player1->setDirection("right", false);}

            // player2
            if (key == SDL_SCANCODE_LEFT) { player2->setDirection("left", false);} 
            if (key == SDL_SCANCODE_RIGHT) { player2->setDirection("right", false);}
        }
    }
}

void Game::update() {
    ball.update(deltaTime);
    player1->update(deltaTime);
    player2->update(deltaTime);

    // collision
    handleBallPlayerCollision(ball, *player1);
    handleBallPlayerCollision(ball, *player2);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    //object
    player1->draw(renderer);
    player2->draw(renderer);
    ball.draw(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyTexture(backgroundTexture);  // Giải phóng ảnh nền
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Game::setDeltaTime(Uint32 &lastTime) {
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;  // Đổi từ ms sang giây
    lastTime = currentTime;
    // std::cout << deltaTime << " " << 1 / deltaTime << std::endl;
}

float Game::getDeltaTime() {
    return deltaTime;
}

void Game::loadBackground(const char* path) {
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

