#include "../headers/audio.h"

bool Audio::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL Audio Init Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cerr << "SDL_mixer Init Failed: " << Mix_GetError() << std::endl;
        return false;
    }

    std::cout << "Total music decoders: " << Mix_GetNumMusicDecoders() << std::endl;
    for (int i = 0; i < Mix_GetNumMusicDecoders(); ++i) {
        std::cout << "Decoder " << i << ": " << Mix_GetMusicDecoder(i) << std::endl;
    }

    return true;
}

void Audio::playMusic(const std::string& filename, int loop) {
    if (Mix_PlayingMusic() && currentMusicFile == filename) {
        return;
    }
    
    if (currentMusic) {
        Mix_FreeMusic(currentMusic);
    }

    currentMusic = Mix_LoadMUS(filename.c_str());
    if (!currentMusic) {
        std::cerr << "Failed to load music: " << filename << " | " << Mix_GetError() << std::endl;
        return;
    }

    currentMusicFile = filename;
    Mix_PlayMusic(currentMusic, loop);
}

void Audio::stopMusic() {
    Mix_HaltMusic();
}

void Audio::playSound(const std::string& filename, int loop) {
    if (soundEffects.find(filename) == soundEffects.end()) {
        Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
        if (!sound) {
            std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
            return;
        }
        soundEffects[filename] = sound;
    }

    Mix_PlayChannel(-1, soundEffects[filename], loop);
}

void Audio::setMusicVolume(int volume) {
    Mix_VolumeMusic(volume);
}

void Audio::setSoundVolume(int volume) {
    for (auto& pair : soundEffects) {
        Mix_VolumeChunk(pair.second, volume);
    }
}


void Audio::cleanup() {
    for (auto& pair : soundEffects) {
        Mix_FreeChunk(pair.second);
    }
    soundEffects.clear();

    if (currentMusic) {
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }

    Mix_CloseAudio();
    SDL_Quit();
}

void Audio::playRandomKick() {
    std::vector<std::string> kicks = {
        KICK1_BALL_PATH,
        KICK2_BALL_PATH,
        KICK3_BALL_PATH
    };

    std::random_device rd;  
    std::mt19937 gen(rd());  // Mersenne Twister 19937
    std::uniform_int_distribution<int> dist(0, kicks.size() - 1);

    int choice = dist(gen);  // Random số 0, 1 hoặc 2
    playSound(kicks[choice]);
}