#include "pipe.h"
#include "stdio.h"

vector<position> posPipe;
threat threats[4];
int time[4]; 
short int cmove = 0; 
bool passed[4]; 

bool pipe::init(){
    posPipe.clear();
    for (signed char i = 0; i < TOTAL_PIPE; i++){
        position temp;
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
        passed[i] = 0; 
        
        threats[i].die = 1; 
        threats[i].posThreat.x = temp.x - 5;
        threats[i].posThreat.y = temp.y + PIPE_SPACE/2 + height();
        threats[i].init(threats[i].posThreat.x, threats[i].posThreat.y); 
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

        if ( !threats[i].die ){
            threats[i].render();
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
                passed[i] = 0; 
            
                if ( cmove > 5 ) cmove = 0; 
                
                if ( !cmove && rand() % 15 == 0 ){
                    cmove = 1; 
                    threats[i].die = 1; 
                }

                if ( cmove ){
                    cmove ++; 
                    threats[i].die = 1; 
                }
                else{
                    if ( rand() % 4 == 0 ) threats[i].die = 0; 
                    else threats[i].die = 1; 
                }

                threats[i].ckfall = 0;
                threats[i].posThreat.x = posPipe[i].x + width()/2 - 25;
                threats[i].posThreat.y = posPipe[i].y + PIPE_SPACE/2 + height() - 25; 
                threats[i].init(threats[i].posThreat.x, threats[i].posThreat.y); 
            }
            else{
                posPipe[i].x -= 3;
                threats[i].posThreat.x -= 3; 
                time[i] ++; 

                if ( cmove ){
                    if ( (time[i]/75)%2 == 0 ){
                        posPipe[i].y -= 1; 
                        threats[i].posThreat.y -= 1; 
                    }
                    else{
                        posPipe[i].y += 1;
                        threats[i].posThreat.y += 1; 
                    }
                }

                if ( threats[i].ckfall ) threats[i].fall(); 
            }
        }
    }
    else{
        cmove = 0; 
    }
}

bool pipe::updateThreat(short int x, short int y){
    for (int i = 0; i < TOTAL_PIPE; i ++) if ( !threats[i].die ){
        if ( x + 20 >= threats[i].posThreat.x - 20 && 
            ( (y >= threats[i].posThreat.y - 10 &&
             y <= threats[i].posThreat.y + 40) || (y + 20 >= threats[i].posThreat.y - 10 && y + 20 <= threats[i].posThreat.y + 40)) ){
            threats[i].ckfall = 1; 
            threats[i].time = 0; 
            cout << threats[i].die << " threats fall\n" ;  
            return true; 
        } 
   }
   else{
        threats[i].free(); 
   }
   return false; 
}