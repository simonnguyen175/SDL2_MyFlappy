#include "ball.h" 

bool ball::init(short int x, short int y){
    string ball_path = "res/image/" + Ball[curChar] + ".png";
    posBall.getPos(x, y);
    Load(ball_path.c_str(), 1); 
    return true; 
}

bool ball::initArrow(short int x, short int y){
    string ball_path = "res/image/arrow.png";
    posBall.getPos(x, y);
    Load(ball_path.c_str(), 1); 
    return true; 
}

void ball::free(){ 
    Free(); 
}

void ball::render(){ 
    Render(posBall.x, posBall.y, angle); 
}

void ball::update(){    
    posBall.x += 10;
    if ( curChar == 0 ) angle += 5;
    if ( curChar == 2 ) angle += 20;
}