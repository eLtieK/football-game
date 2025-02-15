#include "src/headers/game.h"
#include "src/headers/loader.h"

Game game;

int main(int argc, char *argv[]) {
    game.init("Head Soccer", WINDOW_WIDTH, WINDOW_HEIGHT);

    Uint32 lastTime = SDL_GetTicks();
    while (game.running()) {
        game.setDeltaTime(lastTime);
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();
    return 0;
}
