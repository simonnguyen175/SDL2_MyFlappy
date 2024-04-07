#ifndef THREAT_H
#define THREAT_H

#include "textureManager.h"

class threat:LTexture{
    public: 
        bool init(int x, int y); 
        void free(); 
        void update(int delta); 
        void render(); 
        void fall(); 
        bool die = 1, ckfall = 0; 
        short int angle, time = 0, x0;
        position posThreat; 
};

#endif