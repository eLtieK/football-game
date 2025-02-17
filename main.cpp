#include "src/headers/game.h"
#include "src/headers/loader.h"
#include "src/headers/ui.h"

Game game;
Ui ui;

int main(int argc, char *argv[]) {
    game.init("Head Soccer", WINDOW_WIDTH, WINDOW_HEIGHT);
    ui.setRenderer(game.getRenderer());
    ui.init();

    Uint32 lastTime = SDL_GetTicks();
    while (game.running()) {
        game.setDeltaTime(lastTime);
        if (ui.getIsIntro()) {
            ui.handleEvents(game);
            ui.update();
            ui.render();
        } else {
            game.handleEvents();
            game.update();
            game.render();
        }
    }

    game.clean();
    return 0;
}
