#include "threat.h"
#include "iostream"

bool threat::init(short int x, short int y){
    string threat_path = "res/image/bird.png";
    posThreat.getPos(x, y);
    Load(threat_path.c_str(), 1); 
    curFrame = 0; 
    frame[0].x = 0; frame[0].y = 0; frame[0].w = getWidth()/3; frame[0].h = getHeight();
    frame[1].x = getWidth()/3*1; frame[1].y = 0; frame[1].w = getWidth()/3; frame[1].h = getHeight();
    frame[2].x = getWidth()/3*2; frame[2].y = 0; frame[2].w = getWidth()/3; frame[2].h = getHeight();  
    return true; 
}

void threat::free(){
    Free(); 
}

void threat::render(){
    Render(posThreat.x, posThreat.y, 0, &frame[((curFrame)/10)%3]);
    if ( ((curFrame)/15)%2 ) posThreat.y -= 1;
    else posThreat.y += 1; 
    curFrame++;  
}

void threat::fall(){
    if ( posThreat.y > SCREEN_HEIGHT ){
        die = 1; 
        return; 
    }

    if ( time == 0 ) x0 = posThreat.y; 
    
    if ( time >= 0 ){
        posThreat.y = x0 + time * time * 0.18 - 7.3 * time;
        time ++; 
    }
}