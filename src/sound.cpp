#include "sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

int introChannel; 

bool sound::init(){
    string breath_path = "res/sound/breath.wav";
    string hit_path = "res/sound/hit.wav";
    string sound_path = "res/image/sound.png";
    string background_path = "res/sound/backgroundSound.mp3"; 
    string intro_path = "res/sound/intro.wav"; 

    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else{
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ){
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        breath = Mix_LoadWAV( breath_path.c_str() );
        if ( breath == NULL ){
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        hit = Mix_LoadWAV( hit_path.c_str() );
        if (hit == NULL){
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        background = Mix_LoadMUS(background_path.c_str()); 
        intro = Mix_LoadWAV(intro_path.c_str());

        if (!Load(sound_path)){
            return false;
        }

        Active.x = 0; Active.y = 0; Active.w = getWidth(); Active.h = getHeight() / 2;
        Mute.x = 0; Mute.y = getHeight() / 2; Mute.w = getWidth(); Mute.h = getHeight() / 2;
        isPlay = true;
    }
    return success;
}

void sound::free(){
    Free();
    
    Mix_FreeChunk(breath);
    breath = NULL;
    Mix_FreeChunk(hit);
    hit = NULL;

    Mix_Quit();
}

void sound::replayBackground(){
    Mix_HaltMusic(); 
}

void sound::playIntro(){
    if ( isPlay )
        introChannel = Mix_PlayChannel(-1, intro, -1); 
}

void sound::stopIntro(){
    if ( isPlay )
        Mix_HaltChannel(introChannel); 
}

void sound::playBreath(){
    if (isPlay)
        Mix_PlayChannel( -1, breath, 0 );

}

void sound::playHit(){
    cout << "play hit\n"; 
    if (isPlay)
        Mix_PlayChannel(-1, hit, 0);
}

void sound::playBackground(){
    if (isPlay)
        Mix_PlayMusic(background, -1); 
}

void sound::renderSound(){
    if (isPlay)
        Render(POS_X, POS_Y, 0, &Active);
    else
        Render(POS_X, POS_Y, 0, &Mute);
}

bool sound::checkSound(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > POS_X && x < POS_X + getWidth() && y > POS_Y && y < POS_Y + getHeight()){
        isPlay = !isPlay;
        return true;
    }
    return false;
}