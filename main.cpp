#include "src/headers/game.h"
#include "src/headers/loader.h"
#include "src/headers/ui.h"
#include "src/headers/audio.h"

Game game;
Ui ui;

int main(int argc, char *argv[]) {
    game.init("Head Soccer", WINDOW_WIDTH, WINDOW_HEIGHT);
    ui.setRenderer(game.getRenderer());
    ui.init();

    Uint32 lastTime = SDL_GetTicks();
    Audio audio = Audio::getInstance();
    audio.init();
    audio.setMusicVolume(32);
    while (game.running()) {
        game.setDeltaTime(lastTime);
        if (Ui::getIsIntro()) {
            audio.playMusic(MUSIC_PATH);
            ui.handleEvents(game);
            ui.update();
            ui.render();
            game.setStartTime();
        } else {
            audio.playMusic(STADIUM_PATH);
            game.handleEvents();
            game.update();
            game.render();
        }
    }

    game.clean();
    return 0;
}
