#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "textureManager.h"
#include "land.h"
#include "player.h"
#include "sound.h"
#include "pipe.h"
#include "background.h"
#include <fstream>

using namespace std;

class game:LTexture{ 
    public:
        struct input{
            enum type {QUIT, PLAY, NONE, PAUSE, LEFT, RIGHT, SHOOT};
            type Type; 

        };

        input userInput;
        land land;
        player player; 
        pipe pipe; 
        sound sound; 
        background background; 
        
        game(); 
        ~game();

        bool initGraphic();

        bool isQuit(){ 
            return quit; 
        }

        bool isDie(){
            return die;
        }

        int getPipeWidth(){
            return pipe.width(); 
        }

        int getPipeHeight(){
            return pipe.height(); 
        }

        void takeInput(); 
        
        void display(); 
        
        void releaseGraphic(); 

        void renderBackground(); 
        
        void renderScoreSmall(); 

        void renderScoreBig(); 

        void renderBestScore(); 

        void renderMessage(); 

        void renderGameOver(); 
        
        void renderLand(); 
        
        void resume(); 

        void pause(); 

        void renderPauseTab(); 

        void replay(); 

        bool checkReplay(); 

        void Restart(); 
    
    private:
        const double scaleNum = 0.75; 
        short int bestScore;     
};

#endif