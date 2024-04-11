#ifndef PIPE_H 
#define PIPE_H

#include "textureManager.h"
#include "threat.h"
#include <iostream>
#include <vector> 

using namespace std;

extern vector<position> posPipe;
extern bool passed[2]; 
extern threat obs[2];  

class pipe:LTexture{
    private:
        const short int randMin = -373 + 50;
        const short int randMax = SCREEN_HEIGHT - LAND_HEIGHT - PIPE_DISTANCE - 373 - 75;
    public:
        bool init();

        void free();

        void render();

        void update();

        bool updateThreat(short int x, short int y); 

        short int width() {return getWidth();}

        short int height() {return getHeight();}
};

#endif