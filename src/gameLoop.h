#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "textureManager.h"
#include <fstream>


using namespace std;

class game:LTexture{ 
    public:
        struct input{
            enum type {QUIT, PLAY, NONE, PAUSE};
            type Type; 
        };

        input userInput;
        
        game(); 
        ~game();

        bool initGraphic();

        bool isQuit(){ 
            return quit; 
        }

        void takeInput(); 
        
        void display(); 
        
        void releaseGraphic(); 

        void renderBackground(); 
        
        void renderScoreSmall(); 

        void renderScoreBig(); 

        void renderBestScore(); 

        void renderMessage(); 
        
        void renderLand(); 
        
        void resume(); 

        void pause(); 

        void renderPauseTab(); 

        void replay(); 

        bool checkReplay(); 

        void Restart(); 
    
    private:
        const double scaleNum = 0.75; 
        short int score, bestScore;     
};

#endif