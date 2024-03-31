#ifndef BALL_H
#define BALL_H

#include "textureManager.h"

class ball:LTexture{
public:  
    bool init(int x, int y); 
    void free(); 
    void update();
    void render(); 
    short int angle; 
    position posBall; 
};

#endif