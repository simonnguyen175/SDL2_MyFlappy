#ifndef BALL_H
#define BALL_H

#include "textureManager.h"

class ball: public LTexture{
public:  
    bool init(short int x, short int y); 
    bool initArrow(short int x, short int y); 
    void free(); 
    void update();
    void render(); 
    short int angle; 
    position posBall; 
};

#endif