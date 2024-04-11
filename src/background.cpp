#include "background.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool background::init(short int id){
    posBackground.getPos(0, 0);
    string back_path = "res/image/background/layer" + to_string(id) + ".png";
    if ( isNULL() ){
        if ( Load(back_path.c_str(), 1) ){
            cout << "Load " << back_path << '\n'; 
            return true;
        }
        else return false;
    }
    return false;
}

void background::free(){
    Free();
}

void background::render(){
    if (posBackground.x > -getWidth() && posBackground.x <= 0){
        Render(posBackground.x, posBackground.y);
        Render(posBackground.x + getWidth(), posBackground.y, 0, NULL);
    }
    else{
        posBackground.getPos(0, 0);
        Render(posBackground.x, posBackground.y);
    }
}

void background::update(float delta){
    posBackground.x -= delta;
}
