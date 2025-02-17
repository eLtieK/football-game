#ifndef PHYSIC_H
#define PHYSIC_H

#include "loader.h"
#include <cmath>

class Ball;
class Player;

const int JUMP_VELOCITY = -1000;
const int GRAVITY = 5000;

const float BOUNCE_FACTOR = 0.8f; // He so khi bi va cham
const float GROUND_FACTOR = 0.3f; // He so khi bi va cham
const float FRICTION = 0.998f; // He so ma sat ngang

void handleBallCollision(int& x, int& y, float& dx, float& dy, int size);
void handlePlayerCollision(int& x, int &y, int& width, int& height);
bool checkCollision(int ballX, int ballY, int ballSize, int playerX, int playerY, int playerWidth, int playerHeight);
void handleBallPlayerCollision(Ball& ball, Player& player);

#endif