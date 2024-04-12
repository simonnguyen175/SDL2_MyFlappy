#include "player.h"
#include <stdio.h>
#include <iostream>

ball arrow; 
short int timeSpeed = 0; 
bool checkDestroy = 0; 

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

        if ( !timeSpeed && time >= 0 ){
            posPlayer.y = x0 + time * time * 0.18 - 6.0 * time;
            time ++;
        }   

        if ( ahead > 0 && threats[ahead].die && !dclose[ahead] && arrow.isNULL() == 1 && rand() % 312 == 0 ){
            arrow.initArrow(posPlayer.x + 10, SCREEN_HEIGHT); 
        }

        if ( !arrow.isNULL() ){
            arrow.render(); 

            if ( !timeSpeed && arrow.posBall.y < posPlayer.y + getHeight() && arrow.posBall.y > posPlayer.y 
              && arrow.posBall.x > posPlayer.x && arrow.posBall.x < posPlayer.x + getWidth() ){
                die = true; 
                arrow.free(); 
            }

            if ( arrow.posBall.y < 0 ){
                arrow.free(); 
            }
            else{
                arrow.posBall.y -= 10; 
            }
        }

        if ( haveSpeed[ahead] && !timeSpeed ){
            if ( posPlayer.x + 20 >= threats[ahead].posThreat.x - 10 && posPlayer.y >= threats[ahead].posThreat.y - 40 
                && posPlayer.y <= threats[ahead].posThreat.y + 40 ){
                    cout << "collect speed\n"; 
                    vScene = 25; 
                    threats[ahead].free(); 
                    timeSpeed = 75; 
                    checkDestroy = 0; 
            }
        }

        if ( timeSpeed > 0 ){
            timeSpeed --; 
            if ( timeSpeed == 10 ){
                checkDestroy = 1; 
            }
            if ( timeSpeed == 0 ){
                vScene = 3; 
            }
            cout << timeSpeed << ' ' << checkDestroy << '\n'; 
        }

        if ( !timeSpeed && !threats[ahead].die && !threats[ahead].ckfall && posPlayer.x + 20 >= threats[ahead].posThreat.x - 10
            && posPlayer.y >= threats[ahead].posThreat.y - 40 && posPlayer.y <= threats[ahead].posThreat.y + 40 ){
                die = true; 
        }

        if ( !timeSpeed ){
            if ( (posPlayer.x + getWidth() > posPipe[ahead].x + 5) && (posPlayer.x + 5 < posPipe[ahead].x + pipeWidth) &&
             (posPlayer.y + 5 < posPipe[ahead].y + pipeHeight + dclose[ahead] || posPlayer.y  + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 5 - dclose[ahead]) ){
                die = true;
                arrow.free(); 
            }
            else if ( posPlayer.x > posPipe[ahead].x + pipeWidth && !passed[ahead] ){
                passed[ahead] = 1; 
                ahead = (ahead + 1) % TOTAL_PIPE;
                score ++;
            }

        }
        else{
            if ( posPlayer.x > posPipe[ahead].x + pipeWidth && !passed[ahead] ){
                passed[ahead] = 1; 
                ahead = (ahead + 1) % TOTAL_PIPE;
                score ++;
            }
        }

        if ( !timeSpeed && posPlayer.y > SCREEN_HEIGHT - LAND_HEIGHT -  PLAYER_HEIGHT - 5 || posPlayer.y < - 10 ){
            die = true;
            arrow.free(); 
        }
    }
    else{
        timeSpeed = 0;
        vScene = 3; 
    }
}
