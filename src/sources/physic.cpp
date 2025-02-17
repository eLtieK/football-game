#include "../headers/physic.h"
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
    if (y - size -10 >= GROUND) {
        y = GROUND + size + 10;
        dy = -dy * GROUND_FACTOR;

        // stop when velocity too small
        if (abs(dy) <= 250) dy = 0;
    }
}