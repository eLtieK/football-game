#include "src/headers/game.h"

Game game;

int main(int argc, char *argv[]) {
    game.init("Head Soccer", 800, 600);

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();
    return 0;
}
