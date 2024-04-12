#ifndef THREAT_H
#define THREAT_H

#include "textureManager.h"

class threat: public LTexture{
    public: 
        bool init(short int x, short int y); 
        bool initSpeed(short int x, short int y); 
        void free(); 
        void update(short int delta); 
        void render(); 
        void renderSpeed(); 
        void fall(); 
        bool die = 1, ckfall = 0; 
        short int angle, time = 0, x0, curFrame = 0;
        position posThreat; 
        SDL_Rect frame[3]; 
};

#endif