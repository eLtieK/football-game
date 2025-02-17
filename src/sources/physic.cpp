#include "../headers/physic.h"
#include "../headers/player.h"
#include "../headers/ball.h"
#include <ostream>
#include <iostream>

void handleBallCollision(int& x, int& y, float& dx, float& dy, int size) {
    // wall collision
    if (x <= 0) {
        x = 0;
        dx = -dx * BOUNCE_FACTOR;
    } else if (x + size >= WINDOW_WIDTH) {
        x = WINDOW_WIDTH - size;
        dx = -dx * BOUNCE_FACTOR;
    }

    // floor collison
    if (y + size >= GROUND) {
        y = GROUND - size;
        dy = -dy * GROUND_FACTOR;
        std::cout << dy << std::endl;
        if (abs(dy) <= 300) dy = 0;
    } 
}

void handlePlayerCollision(int& x, int &y, int& width, int& height) {
    if (x <= 0) {x = 0;} 
    else if (x + width >= WINDOW_WIDTH) {x = WINDOW_WIDTH - width;}
}

bool checkCollision(int ballX, int ballY, int ballSize, int playerX, int playerY, int playerWidth, int playerHeight) {
    return !(ballX + ballSize < playerX || ballX > playerX + playerWidth ||
             ballY + ballSize < playerY || ballY > playerY + playerHeight);
}

void handleBallPlayerCollision(Ball& ball, Player& player) {
    if (player.getIsCollision()) {return ;} 
    int ballX = ball.getX();
    int ballY = ball.getY();
    int ballSize = ball.getSize();
    float ballDx = ball.getDx();
    float ballDy = ball.getDy();

    int playerX = player.getX();
    int playerY = player.getY();
    int playerWidth = player.getWidth();
    int playerHeight = player.getHeight();

    if (checkCollision(ballX, ballY, ballSize, playerX, playerY, playerWidth, playerHeight)) {
        // Xác định hướng va chạm
        bool hitFromTop = ballY + ballSize >= playerY && ballY <= playerY;  // Bóng va chạm từ trên
        bool hitFromBottom = ballY <= playerY + playerHeight && ballY + ballSize >= playerY + playerHeight;  // Bóng va chạm từ dưới
        bool hitFromLeft = ballX + ballSize >= playerX && ballX <= playerX;  // Bóng va chạm từ trái
        bool hitFromRight = ballX <= playerX + playerWidth && ballX + ballSize >= playerX + playerWidth;  // Bóng va chạm từ phải

        if (hitFromLeft) {
            if (ballX <= 0) ball.applyForce(2200,0);
            else ball.applyForce(-2200,0);
            ball.applyForce(0, -2000);
        } 
        else if (hitFromRight) {
            if (ballX + ballSize >= WINDOW_WIDTH) ball.applyForce(-2200,0);
            else ball.applyForce(2200,0);
            ball.applyForce(0, -2000);
        }
        else if (hitFromTop) {
            ball.applyForce(0,-800);
        } 
        else if (hitFromBottom) {
            ball.applyForce(0, 800);
        }

        player.setIsCollision(true);
    }
}
