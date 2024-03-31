#include "pipe.h"

vector<position> posPipe; 

bool pipe::init(){
    posPipe.clear();
    for (signed char i = 0; i < TOTAL_PIPE; i ++){
        position temp;
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
    }

    if (isNULL()){
        if ( Load( "res/image/pipe.png", 1) )
            return true;
    }
    return false;
}

void pipe::free(){
    Free(); 
}

void pipe::render(){
    for (short int i = 0; i < TOTAL_PIPE; i ++){
        Render(posPipe[i].x, posPipe[i].y);
        Render(posPipe[i].x, posPipe[i].y + getHeight() + PIPE_DISTANCE, 180); 
    }
}

void pipe::update(){
    if ( !die ){
        for (short int i = 0; i < TOTAL_PIPE; i ++){
            if (posPipe[i].x < - getWidth()){
                posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE;    
                
                // if ( rand() % 3 == 0 ) messi[i].die = 0; 
                // else messi[i].die = 1; 

                // messi[i].ckfall = 0;
                // messi[i].posThreat.x = posPipe[i].x + width()/2 - 25;
                // messi[i].posThreat.y = posPipe[i].y + PIPE_SPACE/2 + height() - 25; 
                // messi[i].init(messi[i].posThreat.x, messi[i].posThreat.y); 
            }
            else{
                posPipe[i].x -= 3;
                // messi[i].posThreat.x -= 3; 
                // if ( messi[i].ckfall ) messi[i].fall(); 
            }
        }
    }
}

// bool pipe::updateThreat(short int x, short int y){
//     for (int i = 0; i < 2; i ++) if ( !messi[i].die ){
//         if ( x + 20 >= messi[i].posThreat.x - 20 && 
//             ( (y >= messi[i].posThreat.y - 10 &&
//              y <= messi[i].posThreat.y + 40) || (y + 20 >= messi[i].posThreat.y - 10 && y + 20 <= messi[i].posThreat.y + 40)) ){
//             messi[i].ckfall = 1; 
//             messi[i].time = 0; 
//             return true; 
//         } 
//    }
//    return false; 
// }