#include "../headers/game.h"

const char * BACKGROUND_PATH = "assests/images/background/background2.jpg";
const char * PLAYER1_HEAD_PATH = "assests/images/head/head1/Picture49.png";
const char * PLAYER2_HEAD_PATH = "assests/images/head/head2/Picture50.png";
const char * PLAYER1_SHOE_RUN_PATH = "assests/images/shoe/shoe1/walk";
const char * PLAYER2_SHOE_RUN_PATH = "assests/images/shoe/shoe2/walk";
const char * PLAYER1_SHOE_JUMP_PATH = "assests/images/shoe/shoe1/jump";
const char * PLAYER2_SHOE_JUMP_PATH = "assests/images/shoe/shoe2/jump";
const char * BALL_PATH = "assests/images/ball/ball.png";
const char * SMOKE_PATH = "assests/images/smoke";

void Game::init(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_JPG);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    isRunning = true;
    
    player1 = new Player();
    player2 = new Player();
    player1->init(WINDOW_WIDTH / 2 - 400 , GROUND - player1->getRealHeight(), true, this->renderer);
    player2->init(WINDOW_WIDTH / 2 + 400 - player2->getWidth(), GROUND - player2->getRealHeight(), false, this->renderer);

    goalLeft = new Goal(); goalLeft->setIsLeft(true);
    goalRight = new Goal(); goalRight->setIsLeft(false);
    goalLeft->init(0, GROUND - goalLeft->getHeight());
    goalRight->init(WINDOW_WIDTH - goalRight->getWidth(), GROUND - goalRight->getHeight());

    ball.init(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

    smoke = new AnimationSprite();
    smoke->init(200,200,6,50);

    // load texture
    loadBackground(BACKGROUND_PATH);
    player1->loadHeadTexture(PLAYER1_HEAD_PATH, renderer);
    player2->loadHeadTexture(PLAYER2_HEAD_PATH, renderer);

    player1->loadShoeRunTexture(PLAYER1_SHOE_RUN_PATH, renderer);
    player2->loadShoeRunTexture(PLAYER2_SHOE_RUN_PATH, renderer);

    player1->loadShoeJumpTexture(PLAYER1_SHOE_JUMP_PATH, renderer);
    player2->loadShoeJumpTexture(PLAYER2_SHOE_JUMP_PATH, renderer);

    ball.loadBallTexture(BALL_PATH, renderer);
    smoke->loadTexture(SMOKE_PATH, renderer);

    // Ui
    game_clock = new UiText();
    game_clock->setRenderer(renderer);
    game_clock->init("0:" + std::to_string(currentTime), {255,255,255,255}, 80);
    game_clock->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6);
    game_clock->setIsOutline(true);

    uiLogic.init(renderer);
    gameOverScreen.init(renderer);
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
    if (this->isPause) {
        std::string str = gameOverScreen.update();
        if (str == "playAgain") {this->restartScreen();}
        if (str == "mainMenu") {
            Ui::setIsIntro(true);
            this->restartScreen();
        }
        if (str == "quit") {isRunning = false;}
        return;
    }
    //Ai
    if (this->isAi) {
        player2->updateAI(ball.getX(), ball.getY(), "right");
        // player1->updateAI(ball.getX(), ball.getY(), "left");
    }

    ball.update(deltaTime);
    player1->update(deltaTime);
    player2->update(deltaTime);
    smoke->update(deltaTime);
    goalLeft->update();
    goalRight->update();

    // // collision
    handleBallPlayerCollision(ball, *player1, *smoke);
    handleBallPlayerCollision(ball, *player2, *smoke);
    handleBallGoalCollision(ball, *goalLeft, uiLogic);
    handleBallGoalCollision(ball, *goalRight, uiLogic);

    // // Ui
    updateClock();
}

void Game::updateClock() {
    currentTime = (maxTime - (SDL_GetTicks() - startTime) / 1000);
    currentTime = std::max(currentTime, 0);

    std::string str;
    if (currentTime < 10) {str = "0:0" + std::to_string(currentTime);}
    else {str = "0:" + std::to_string(currentTime);}
    game_clock->setName(str);
    if (currentTime == 0) {
        this->setIsPause(true);
        gameOverScreen.setGameover(uiLogic.getPlayerWin());
    }
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
    smoke->draw(renderer);
    goalLeft->draw(renderer);
    goalRight->draw(renderer);

    //ui
    game_clock->draw();
    uiLogic.draw();

    if(this->isPause) {gameOverScreen.draw();}

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    if (player1) {
        delete player1;
        player1 = nullptr;
    }
    if (player2) {
        delete player2;
        player2 = nullptr;
    }
    if (goalLeft) {
        delete goalLeft;
        goalLeft = nullptr;
    }
    if (goalRight) {
        delete goalRight;
        goalRight = nullptr;
    }
    if (smoke) {
        delete smoke;
        smoke = nullptr;
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_DestroyTexture(backgroundTexture);  // Giải phóng ảnh nền
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

void Game::restartScreen() {
    player1->setPos(WINDOW_WIDTH / 2 - 400, GROUND - player1->getRealHeight());
    player2->setPos(WINDOW_WIDTH / 2 + 400 - player2->getWidth(), GROUND - player2->getRealHeight());
    
    //check ai player2
    player2->setDirection("left", false);
    player2->setDirection("right", false);

    ball.init(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
    ball.setDx(0); ball.setDy(0);
    uiLogic.resetScore();
    setStartTime();
    setIsPause(false);
}
