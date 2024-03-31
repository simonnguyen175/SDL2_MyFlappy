#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <string>
#include "textureManager.h"

using namespace std;

class sound:LTexture{
    private:
        const short int POS_X = 107;
        const short int POS_Y = 267;
        bool isPlay = 0;
        Mix_Chunk* breath = NULL;
        Mix_Chunk* hit = NULL;
        Mix_Chunk* drop = NULL;
        SDL_Rect Mute ;
        SDL_Rect Active ;

    public:
        bool init();

        void free();

        void playBreath();

        void playHit();

        void renderSound();

        bool checkSound();
};

#endif