#include "../headers/player.h"

void Player::init(int x, int y, bool isPlayer1, SDL_Renderer* renderer) {
    this->x = x;
    this->y = y;
    nametag = new UiText();
    nametag->setRenderer(renderer);
    if (isPlayer1) {nametag->init("Player 1", {0,175,255,255}, 40); nametag->setIsPlayer1(true);} 
    else {nametag->init("Player 2", {255,128,0,255}, 40); nametag->setIsPlayer1(false);} 
}

void Player::updateShoeAnimation() {
    Uint32 now = SDL_GetTicks();
    if(now - lastFrameTime >= frame_delay) {
        frame_index = (frame_index + 1) % SHOE_FRAMES;
        lastFrameTime = now;
    }
}

void Player::update(float dt) {
    move(dt);
    checkCollisionAndReset();
}

void Player::updateAI(int ballX, int ballY, std::string team) {
    // Nếu bóng bên trái, đi sang trái
    int midfield = WINDOW_WIDTH / 2;
    if (!((team == "left" && ballX <= midfield) || (team == "right" && ballX >= midfield))) {
        if (team == "right" && this->x < midfield + midfield / 4) {
            setDirection("right", true);
            setDirection("left", false);
        } else if (team == "left" && this->x > midfield - midfield / 4) {
            setDirection("left", true);
            setDirection("right", false);
        }
        else {
            setDirection("left", false);
            setDirection("right", false);
        }
        return;
    }
    
    if (ballX < x) {
        setDirection("left", true);
        setDirection("right", false);
    } 
    // Nếu bóng bên phải, đi sang phải
    else if (ballX > x) {
        setDirection("right", true);
        setDirection("left", false);
    } 
    // Nếu gần bóng, dừng lại
    else {
        setDirection("left", false);
        setDirection("right", false);
    }

    // Nếu bóng cao hơn AI và AI chưa nhảy, thì nhảy
    if (ballY < y - 50 && !isJumping) {
        jump();
    }
}

void Player::checkCollisionAndReset() {
    Uint32 currentTime = SDL_GetTicks(); 
    if (currentTime - lastCollisionTime >= resetInterval) {
        lastCollisionTime = currentTime;
        isCollision = false;
    }
}

void Player::move(float dt) {
    int dx = 0;

    // left and right
    if (direction_right && direction_left) {dx = 0; this->setStandAnimation();}
    else if (direction_left) {dx = -1; this->updateShoeAnimation();}
    else if (direction_right) {dx = 1; this->updateShoeAnimation();}
    else {this->setStandAnimation();}
    x += dx * speed * dt;
    
    // jump
    if (isJumping) {
        velocityY += GRAVITY * dt;
        y += velocityY * dt;
    }

    // reset jump
    if (y >= GROUND - this->getRealHeight()) {
        y = GROUND - this->getRealHeight();
        isJumping = false;
        velocityY = 0;
        player_state = RUN;
    }

    handlePlayerCollision(x, y, this->getWidth(), this->getRealHeight());

    int offset = OFFSET_HEAD_FRONT;
    if(nametag->getIsPlayer1()) {offset = -offset;}
    nametag->setPosition(x + this->h_width / 2 + offset, y - OFFSET_HEAD_NAME);
}

void Player::setDirection(std::string dir, bool isMove) {
    if (dir == "left") direction_left = isMove;
    if (dir == "right") direction_right = isMove;
}

void Player::jump() {
    if (!isJumping) { 
        isJumping = true;
        velocityY = JUMP_VELOCITY;
        player_state = JUMP;
        // Audio::getInstance().playSound(JUMP_PATH);
    }
}

void Player::draw(SDL_Renderer* renderer) {
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng (RGBA)
    // SDL_Rect debugRect = {x, y - 20, s_width, s_height + h_height - OFFSET_HEAD_SHOE - OFFSET_SHOE_BOT}; // Hình vuông test
    // SDL_RenderFillRect(renderer, &debugRect); 
    SDL_Texture** frames;
    if (player_state == RUN) {frames = playerShoeRunTexture;}
    else if (player_state == JUMP) {frames = playerShoeJumpTexture;}

    if (frames) {
        SDL_Rect rect = {x, y - OFFSET_HEAD_SHOE + h_height, s_width, s_height}; // Vị trí và kích thước vẽ ảnh
        SDL_RenderCopy(renderer, frames[frame_index], NULL, &rect);
    } else {
        SDL_Log("Texture is null, can't render player.");
    }

    // SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Màu trắng (RGBA)
    // SDL_Rect debugRect2 = {x, y + OFFSET_HEAD_SHOE, h_width, h_height}; // Hình vuông test
    // SDL_RenderFillRect(renderer, &debugRect2); 

    if (playerHeadTexture) {
        SDL_Rect rect = {x, y - OFFSET_SHOE_BOT, h_width, h_height}; // Vị trí và kích thước vẽ ảnh
        SDL_RenderCopy(renderer, playerHeadTexture, NULL, &rect);
    } else {
        SDL_Log("Texture is null, can't render player.");
    }

    nametag->draw();
}

void Player::loadHeadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Can't load %s: %s", path, IMG_GetError());
    }
    
    playerHeadTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FreeSurface(surface);
    if (!playerHeadTexture) {
        SDL_Log("Can't create texture: %s", SDL_GetError());
    }
}

void Player::loadShoeRunTexture(const char* path, SDL_Renderer* renderer) {
    for (int i = 0; i < SHOE_FRAMES; i++) {
        std::string filePath = std::string(path) + "/" + std::to_string(i + 1) + ".png"; 
        SDL_Surface* surface = IMG_Load(filePath.c_str());

        if (!surface) {
            SDL_Log("Failed to load %s: %s", filePath.c_str(), SDL_GetError());
            continue;
        }

        playerShoeRunTexture[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void Player::loadShoeJumpTexture(const char* path, SDL_Renderer* renderer) {
    for (int i = 0; i < SHOE_FRAMES; i++) {
        std::string filePath = std::string(path) + "/" + std::to_string(i + 1) + ".png"; 
        SDL_Surface* surface = IMG_Load(filePath.c_str());

        if (!surface) {
            SDL_Log("Failed to load %s: %s", filePath.c_str(), SDL_GetError());
            continue;
        }

        playerShoeJumpTexture[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}