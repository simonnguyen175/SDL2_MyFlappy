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
    bool isHelpMenu = 0; 
    bool backgroundSound = 0; 
    vector<ball> ballBucket; 

    while ( !g.isQuit() ){
        frameStart = SDL_GetTicks(); 
        if ( g.isDie() ){
            ballBucket.clear(); 
            isPause = 0;
            isHelpMenu = 0;
            if ( begin ){
                isMenu = 0;
                begin = 0;     
                g.sound.playIntro(); 
            }
            else isMenu = 1; 

            if ( isMenu ){
                g.sound.playHit(); 
                g.player.render(); 
                g.sound.replayBackground(); 
                backgroundSound = 0; 
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
                    g.renderGameTitle(); 
                    g.score = 0; 
                    g.pipe.init(); 
                    g.player.init(75, SCREEN_HEIGHT / 2 - 10);
                    g.player.render(); 
                    g.renderMessage(); 

                    if ( g.userInput.Type == game::input::PAUSE ){
                        isPause = abs(1- isPause); 
                        g.userInput.Type = game::input::NONE; 
                    }

                    if ( isHelpMenu ){
                        g.renderHelpMenu(); 
                        g.exit(); 
                        g.help(); 
                        
                        if ( g.userInput.Type == game::input::PLAY ){
                            if ( g.checkHelp() ){
                                isHelpMenu = abs(1-isHelpMenu); 
                            }
                            else if ( g.checkExit() ){
                                g.quit = true; 
                            }
                            g.userInput.Type = game::input::NONE; 
                        }
                    }
                    else if ( isPause ){
                        g.resume(); 
                        g.renderPauseTab(); 
                        g.renderScoreSmall(); 
                        g.renderBestScore(); 
                        g.sound.renderSound(); 
                        g.curCharacter(); 
                        g.nextButton(); 
                        g.exit(); 
                        g.help();
   
                        if ( g.userInput.Type == game::input::PLAY ){
                            if ( g.sound.checkSound() ){
                                isSound = abs(1- isSound); 
                            }
                            else if ( g.changeCharacter() ){
                                g.player.init(75, SCREEN_HEIGHT / 2 - 10); 
                            }
                            else if ( g.checkHelp() ){
                                isHelpMenu = abs(1-isHelpMenu); 
                            }
                            else if ( g.checkExit() ){
                                g.quit = true; 
                            }
                            g.userInput.Type = game::input::NONE; 
                        }
                    }
                    else g.pause();

                    if ( g.userInput.Type == game::input::PLAY ){
                        cout << "play\n"; 
                        g.Restart();
                        isMenu = 0;
                        g.userInput.Type = game::input::NONE;
                        if ( isSound && !backgroundSound ){
                            g.sound.stopIntro(); 
                            g.sound.playBackground(); 
                            backgroundSound = 1; 
                        }
                    }
                    g.land.update();    
                }

                g.display();
            }
            g.pipe.init(); 
        }
        else{
            g.takeInput(); 

            if ( !isSound ){
                g.sound.background = NULL; 
            }
             
            if ( g.userInput.Type == game::input::PAUSE ){
                isPause = abs(1- isPause); 
                g.userInput.Type = game::input::NONE; 
            }  

            if ( isPause == 0 && g.userInput.Type == game::input::PLAY && timeSpeed == 0 ){
                if ( isSound ) g.sound.playBreath(); 
                g.player.resetTime(); 
                g.userInput.Type = game::input::NONE; 
            }

            g.renderBackground(); 
            if ( checkDestroy == 1 ){
                g.pipe.init(); 
                arrow.free(); 
                checkDestroy = 0; 
            }
            g.pipe.render(); 
            g.land.render(); 
            g.player.render(); 
            g.renderScoreBig(); 

            for (auto &curB : ballBucket) curB.render(); 

            if (isPause == 0 && g.userInput.Type == game::input::SHOOT){
                ball newBall;
                newBall.init(g.player.posPlayer.x + g.player.getWidth() - 30, g.player.posPlayer.y + g.player.getHeight() - 20); 
                ballBucket.push_back(newBall); 
                g.userInput.Type = game::input::NONE;
            }

            if ( !isPause ){
                if (isPause == 0 && g.userInput.Type == game::input::LEFT){
                    g.player.posPlayer.x -= 55;
                    g.userInput.Type = game::input::NONE; 
                }

                if (isPause == 0 && g.userInput.Type == game::input::RIGHT){
                    g.player.posPlayer.x += 55;
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
                g.updateBackground(); 
                g.pause();
            }
            else{
                if ( isHelpMenu ){
                    g.renderHelpMenu(); 
                    g.exit(); 
                    g.help(); 
                    g.resume();
                    
                    if ( g.userInput.Type == game::input::PLAY ){
                        if ( g.checkHelp() ){
                            isHelpMenu = abs(1-isHelpMenu); 
                        }
                        else if ( g.checkExit() ){
                            g.quit = true; 
                        }
                        g.userInput.Type = game::input::NONE; 
                    }
                }
                else{
                    g.resume(); 
                    g.renderPauseTab(); 
                    g.renderScoreSmall(); 
                    g.renderBestScore(); 
                    g.sound.renderSound(); 
                    g.curCharacter(); 
                    g.nextButton(); 
                    g.exit(); 
                    g.help();

                    if ( g.userInput.Type == game::input::PLAY ){
                        if ( g.sound.checkSound() ){
                            isSound = abs(1- isSound); 
                        }
                        else if ( g.changeCharacter() ){
                            short int cx = g.player.posPlayer.x;
                            short int cy = g.player.posPlayer.y; 
                            g.player.init(cx, cy); 
                        }
                        else if ( g.checkHelp() ){
                            isHelpMenu = abs(1-isHelpMenu); 
                        }
                        else if ( g.checkExit() ){
                            g.quit = true; 
                        }
                        g.userInput.Type = game::input::NONE; 
                    }
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