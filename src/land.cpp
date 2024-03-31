#include "land.h"
#include <stdio.h>
#include <iostream>

bool land::init(){
    posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
    if (isNULL()){
        if ( Load("res/image/land.png", 1) ) return true;
        else return false;
    }
    return false;   
}

void land::free(){
    Free(); 
}

void land::render(){
    if (posLand.x > 0)
        Render(posLand.x, posLand.y);
    else if (posLand.x > -SCREEN_WIDTH && posLand.x <= 0){
        Render(posLand.x, posLand.y);
        Render(posLand.x + SCREEN_WIDTH, posLand.y, 0, NULL);
    }
    else{
        posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
        Render(posLand.x, posLand.y);
    }
}

void land::update(){
    posLand.x -= 3; 
}

