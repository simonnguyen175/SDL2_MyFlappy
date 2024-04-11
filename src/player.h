#ifndef PLAYER_H
#define PLAYER_H

#include "textureManager.h"
#include "pipe.h"

using namespace std;

class player: public LTexture{
    public:
        bool init();

        void render();

        void free();

        void resetTime(){
            time = 0;
        }

        void fall();

        void update(short int pileWidth, short int pileHeight);

        short int angle, time, x0;
        short int ahead = 0;
        position posPlayer;
};

#endif