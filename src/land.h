#ifndef LAND_H
#define LAND_H

#include "textureManager.h"
#include "pipe.h"
#include <vector>

using namespace std;

class land:LTexture{
    private: 
        position posLand;
    public: 
        bool init(); 
        
        void free();

        void render(); 

        void update(); 
};

#endif 