#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "textureManager.h"
#include "gameLoop.h"
#include "ball.h" 

using namespace std; 

int main(int argc, char* argv[]){
    const short int FPS = 60;
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
                
                g.background.render(); 
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
        else{
            g.takeInput(); 

            if ( g.userInput.Type == game::input::PAUSE ){
                isPause = abs(1- isPause); 
                g.userInput.Type = game::input::NONE; 
            }  

            if ( isPause == 0 && g.userInput.Type == game::input::PLAY ){
                if ( isSound ) g.sound.playBreath(); 
                g.player.resetTime(); 
                g.userInput.Type = game::input::NONE; 
            }

            g.background.render(); 
            g.pipe.render(); 
            g.land.render(); 
            g.player.render(); 
            g.renderScoreBig(); 

            for (auto &curB : ballBucket) curB.render(); 

            if (isPause == 0 && g.userInput.Type == game::input::SHOOT){
                ball newBall;
                newBall.init(g.player.posPlayer.x + g.player.getWidth() - 30, g.player.posPlayer.y + g.player.getHeight() - 30); 
                ballBucket.push_back(newBall); 
                g.userInput.Type = game::input::NONE;
            }

            if ( !isPause ){
                if (isPause == 0 && g.userInput.Type == game::input::LEFT){
                    g.player.posPlayer.x -= 50;
                    g.userInput.Type = game::input::NONE; 
                }

                if (isPause == 0 && g.userInput.Type == game::input::RIGHT){
                    g.player.posPlayer.x += 50;
                    g.userInput.Type = game::input::NONE; 
                }

                g.player.update(g.getPipeWidth(), g.getPipeHeight());

                for (auto &curB : ballBucket)
                    curB.update();

                g.pipe.update();
                for (int i = 0; i < ballBucket.size(); i ++){
                    if ( g.pipe.updateThreat(ballBucket[i].posBall.x, ballBucket[i].posBall.y) || ballBucket[i].posBall.x >= SCREEN_WIDTH ){ 
                        ballBucket[i].free();
                        ballBucket.erase(ballBucket.begin() + i); 
                    }
                }

                g.land.update();
                g.background.update(); 
                g.pause();
            }
            else{
                g.resume(); 
                g.renderPauseTab(); 
                g.renderScoreSmall(); 
                g.renderBestScore(); 
                g.replay(); 
                g.sound.renderSound(); 
                g.curCharacter(); 
                g.nextButton(); 
                
                if ( g.userInput.Type == game::input::PLAY ){
                    if ( g.checkReplay() ){
                        isPause = 0;
                    }   
                    else if ( g.sound.checkSound() ){
                        isSound = abs(1- isSound); 
                    }
                    else if ( g.changeCharacter() ){
                        g.player.init(); 
                    }
                    g.userInput.Type = game::input::NONE; 
                }
            }
            
            g.display(); 
        }

        // Limit FPS
        frameTime = SDL_GetTicks() - frameStart;
        if ( frameDelay > frameTime ){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;        
}