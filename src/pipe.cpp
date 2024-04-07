#include "pipe.h"
#include "threat.h"
#include "stdio.h"

vector<position> posPipe;
threat obs[2];
int time[2]; 

bool pipe::init(){
    posPipe.clear();
    for (signed char i = 0; i < TOTAL_PIPE; i++){
        position temp;
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
        
        obs[i].die = 1; 
        obs[i].posThreat.x = temp.x - 5;
        obs[i].posThreat.y = temp.y + PIPE_SPACE/2 + height();
        obs[i].init(obs[i].posThreat.x, obs[i].posThreat.y); 
    }

    if (isNULL()){
        if (Load( "res/image/pipe.png", 1 )){
            return true;
        }
    }
    return false;
}

void pipe::free(){
    Free();
}

void pipe::render(){
    for (signed char i = 0; i < TOTAL_PIPE; i++){
        Render(posPipe[i].x, posPipe[i].y);
        Render(posPipe[i].x, posPipe[i].y + getHeight() + PIPE_SPACE, 180); 

        if ( !obs[i].die ){
            obs[i].render();
        }
    }
}

void pipe::update(){
    if (!die){
        for (signed char i = 0; i < TOTAL_PIPE; i++){
            if ( posPipe[i].x < -getWidth() ){
                posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE;   
                time[i] = 0;

                if ( rand() % 3 == 0 ) obs[i].die = 0; 
                else obs[i].die = 1; 

                obs[i].ckfall = 0;
                obs[i].posThreat.x = posPipe[i].x + width()/2 - 25;
                obs[i].posThreat.y = posPipe[i].y + PIPE_SPACE/2 + height() - 25; 
                obs[i].init(obs[i].posThreat.x, obs[i].posThreat.y); 
            }
            else{
                posPipe[i].x -= 3;
                obs[i].posThreat.x -= 3; 
                time[i] ++; 
                if ( (time[i]/75)%2 == 0 ){
                    posPipe[i].y -= 0.5; 
                    obs[i].posThreat.y -= 0.5; 
                }
                else{
                    cout << "pipe down\n"; 
                    posPipe[i].y += 0.5;
                    obs[i].posThreat.y += 0.5; 
                }

                if ( obs[i].ckfall ) obs[i].fall(); 
            }
        }
    }
}

bool pipe::updateThreat(short int x, short int y){
    for (int i = 0; i < 2; i ++) if ( !obs[i].die ){
        if ( x + 20 >= obs[i].posThreat.x - 20 && 
            ( (y >= obs[i].posThreat.y - 10 &&
             y <= obs[i].posThreat.y + 40) || (y + 20 >= obs[i].posThreat.y - 10 && y + 20 <= obs[i].posThreat.y + 40)) ){
            obs[i].ckfall = 1; 
            obs[i].time = 0; 
            cout << obs[i].die << " obs fall\n" ;  
            return true; 
        } 
   }
   return false; 
}