#include "../headers/physic.h"
#include "../headers/player.h"
#include "../headers/ball.h"
#include "../headers/logic.h"
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
        if (abs(dy) <= 300) dy = 0;
    } else if (y < 0) {
        y = 0;
        dy = -dy * BOUNCE_FACTOR;
    } 
}

void handlePlayerCollision(int& x, int &y, int width, int height) {
    if (x <= 0) {x = 0;} 
    else if (x + width >= WINDOW_WIDTH) {x = WINDOW_WIDTH - width;}
}

bool checkCollision(int ballX, int ballY, int ballSize, int playerX, int playerY, int playerWidth, int playerHeight) {
    return !(ballX + ballSize < playerX || ballX > playerX + playerWidth ||
             ballY + ballSize < playerY || ballY > playerY + playerHeight );
}

void handleBallPlayerCollision(Ball& ball, Player& player, AnimationSprite& smoke) {
    if (player.getIsCollision()) {return ;} 
    int ballX = ball.getX();
    int ballY = ball.getY();
    int ballSize = ball.getSize();
    float ballDx = ball.getDx();
    float ballDy = ball.getDy();

    int playerX = player.getX();
    int playerY = player.getY();
    int playerWidth = player.getWidth();
    int playerHeight = player.getRealHeight();

    // std::cout << playerY << " " << playerHeight << std::endl;

    if (checkCollision(ballX, ballY, ballSize, playerX, playerY, playerWidth, playerHeight)) {
        // Xác định hướng va chạm
        smoke.setPos(ballX, ballY);
        smoke.setVisible(true);
        
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

void handleBallGoalCollision(Ball& ball, Goal& goal, GameLogic& uiLogic) {
    int ballX = ball.getX();
    int ballY = ball.getY();
    int ballSize = ball.getSize();
    float ballDx = ball.getDx();
    float ballDy = ball.getDy();

    int goalX = goal.getRect().x;
    int goalY = goal.getRect().y;
    int goalWidth = goal.getRect().w;
    int goalHeight = goal.getRect().h;

    // std::cout << playerY << " " << playerHeight << std::endl;

    if (checkCollision(ballX, ballY, ballSize, goalX, goalY, goalWidth, goalHeight)) {
        // Xác định hướng va chạm
        
        bool hitFromTop = ballY + ballSize >= goalY && ballY <= goalY;  // Bóng va chạm từ trên
        bool hitFromLeft = ballX + ballSize >= goalX && ballX <= goalX;  // Bóng va chạm từ trái
        bool hitFromRight = ballX <= goalX + goalWidth && ballX + ballSize >= goalX + goalWidth;  // Bóng va chạm từ phải

        if (hitFromTop) {ball.applyForce(0,-ballDy * BOUNCE_FACTOR);} 
        else if (hitFromLeft || hitFromLeft) {
            goal.setGoal();

            if (goal.getIsLeft()) {uiLogic.addScore(1, "player2");}
            else {uiLogic.addScore(1,"player1");}

            ball.setX(WINDOW_WIDTH / 2); ball.setY(WINDOW_HEIGHT / 4);
            ball.setDx(0); ball.setDy(0);
        } 
    } 
}
