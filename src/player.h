#ifndef PLAYER_H
#define PLAYER_H

#include "textureManager.h"
#include "pipe.h"
#include "ball.h"

using namespace std;

extern ball arrow; 
extern short int timeSpeed;
extern bool checkDestroy; 

class player: public LTexture{
    public:
        bool init(short int x, short int y);

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