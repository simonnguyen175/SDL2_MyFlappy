#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "textureManager.h"
#include "gameLoop.h"
#include "ball.h" 

using namespace std; 

int main(int argc, char* argv[]){
    const short int FPS = 65;
    const short int frameDelay = 1000/FPS; 
    Uint32 frameStart;
    short int frameTime; 
    

    game g;
    bool isMenu = 0;
    bool isPause = 0;
    bool isSound = 1;
    bool begin = 1; 
    vector<ball> ballBucket; 

    while ( !g.isQuit() ){
        frameStart = SDL_GetTicks(); 
        if ( g.isDie() ){
            ballBucket.clear(); 
            if ( begin ){
                isMenu = 0;
                begin = 0; 
            }
            else isMenu = 1; 

            if ( isMenu ){
                g.sound.playHit(); 
                g.player.render(); 
            }

            g.userInput.Type = game::input::NONE;
            
            while ( g.isDie() && !g.isQuit() ){
                g.takeInput(); 
                if ( isMenu == 1 && g.userInput.Type == game::input::PLAY ){
                    if ( g.checkReplay() ) isMenu = 0;
                    g.userInput.Type = game::input::NONE; 
                }

                g.renderBackground(); 
                g.pipe.render(); 
                g.land.render(); 

                if ( isMenu ){
                    g.player.render(); 
                    g.player.fall(); 
                    g.renderGameOver(); 
                    g.renderScoreSmall(); 
                    g.renderBestScore(); 
                    g.replay(); 
                }
                else{
                    g.pipe.init(); 
                    g.player.init();
                    g.player.render(); 
                    g.renderMessage(); 
                    if ( g.userInput.Type == game::input::PLAY ){
                        cout << "play\n"; 
                        g.Restart();
                        isMenu = 0;
                        g.userInput.Type = game::input::NONE;
                    }
                    g.land.update();    
                }

                g.display();
            }
            g.pipe.init(); 
        }
        

        // Limit FPS
        frameTime = SDL_GetTicks() - frameStart;
        if ( frameDelay > frameTime ){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;        
}