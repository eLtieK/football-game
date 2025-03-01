#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>  // Thư viện random hiện đại

const std::string MUSIC_PATH = "assests/sounds/musics/theme.mp3";
const std::string STADIUM_PATH = "assests/sounds/stadium.mp3";

const std::string KICK1_BALL_PATH = "assests/sounds/kick.mp3";
const std::string KICK2_BALL_PATH = "assests/sounds/kick2.wav";
const std::string KICK3_BALL_PATH = "assests/sounds/kick3.wav";

const std::string CROSSBAR_PATH = "assests/sounds/crossbar.mp3";
const std::string GOAL_PATH = "assests/sounds/goal.mp3";
const std::string JUMP_PATH = "assests/sounds/jump.wav";

    class Audio {
    public:
        static Audio& getInstance() {
            static Audio instance;
            return instance;
        }

        bool init();
        void playMusic(const std::string& filename, int loop = -1);
        void playSound(const std::string& filename, int loop = 0);
        void stopMusic();
        void setMusicVolume(int volume);
        void setSoundVolume(int volume);
        void cleanup();

        //special
        void playRandomKick();

    private:
        std::unordered_map<std::string, Mix_Chunk*> soundEffects;
        Mix_Music* currentMusic = nullptr;
        std::string currentMusicFile;  // Lưu file nhạc hiện tại
    };

#endif // AUDIO_H
