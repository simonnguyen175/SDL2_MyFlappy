#include "player.h"
#include <stdio.h>
#include <iostream>

bool player::init(short int x, short int y){
    string player_path = "res/image/" + character[curChar] + ".png";
    Load(player_path.c_str(), 1);
    posPlayer.getPos(x, y);
    ahead = 0;
    angle = 0;
    return true; 
}

void player::free(){
    Free();
}

void player::render(){
    Render(posPlayer.x, posPlayer.y, angle);
}

void player::fall() {
    if ( posPlayer.y < SCREEN_HEIGHT - LAND_HEIGHT - PLAYER_HEIGHT - 5 ){   
        if ( time == 0 ){
            x0 = posPlayer.y;
            angle = -25;
        }
        else if ( angle < 70 && time > 30 ){
            angle += 3; 
        }

        if (time >= 0){
            posPlayer.y = x0 + time * time * 0.18 - 6.0 * time;
            time ++;
        }
    }
    else return;
}

void player::update(short int pipeWidth, short int pipeHeight){
    if ( !die ){
        if ( time == 0 ){
            x0 = posPlayer.y;
            // angle = -25;
        }
        // else if ( angle < 70 && time > 30 ){
        //     angle += 3;
        // }

        if (time >= 0){
            posPlayer.y = x0 + time * time * 0.18 - 6.0 * time;
            time ++;
        }

        if ( !threats[ahead].die && !threats[ahead].ckfall && posPlayer.x + 20 >= threats[ahead].posThreat.x - 10
            && posPlayer.y >= threats[ahead].posThreat.y - 40 && posPlayer.y <= threats[ahead].posThreat.y + 40 ){
                die = true; 
        }

        if ( (posPlayer.x + getWidth() > posPipe[ahead].x + 5) && (posPlayer.x + 5 < posPipe[ahead].x + pipeWidth) &&
             (posPlayer.y + 5 < posPipe[ahead].y + pipeHeight || posPlayer.y  + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 5) ){
            die = true;
        }
        else if ( posPlayer.x > posPipe[ahead].x + pipeWidth && !passed[ahead] ){
            passed[ahead] = 1; 
            ahead = (ahead + 1) % TOTAL_PIPE;
            score ++;
        }

        if (posPlayer.y > SCREEN_HEIGHT - LAND_HEIGHT -  PLAYER_HEIGHT - 5 || posPlayer.y < - 10 ){
            die = true;
        }
    }
}
