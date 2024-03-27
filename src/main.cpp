#include<stdio.h>
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"textureManager.h"
#include"gameLoop.h"

using namespace std; 

int main(int argc, char* argv[]){
    game g;
    while ( !g.isQuit() ){
        g.takeInput(); 
        g.renderBackground(); 
        g.display(); 
    }

    return 0; 
}