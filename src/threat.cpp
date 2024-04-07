#include "threat.h"
#include "iostream"

bool threat::init(int x, int y){
    string threat_path = "res/image/messi.png";
    posThreat.getPos(x, y);
    Load(threat_path.c_str(), 1.02); 
    return true; 
}

void threat::free(){
    Free(); 
}

void threat::render(){
    Render(posThreat.x, posThreat.y);
}

void threat::update(int delta){
    posThreat.x += delta;
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