#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<vector>
#include<stdio.h> 
#include<iostream> 

using namespace std;

static const short int SCREEN_WIDTH = 350;
static const short int SCREEN_HEIGHT = 625;
const string character[] = {"ronaldo", "putin"}; 
const string Ball[] = {"ballpxl", "bulletpxl"}; 
const string Threat[] = {"messi", "nato"}; 

class LTexture{
    public:
        // Texture func and val
        LTexture(); 
        ~LTexture() {}

        bool isNULL(); 

        bool Load(string path, double scale = 1); 

        short int getWidth();
        short int getHeight();

        void Free();
        void Render(short int x, short int y, short int angle = 0, SDL_Rect* srcrect = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        SDL_Texture* Texture;
        short int tWidth;
        short int tHeight; 
   
        // Common val
        static SDL_Window* gWindow;
        static SDL_Renderer* gRenderer;
        static SDL_Event event; 
        static bool quit; 
        static bool die;
        static short int score;
        static short int curChar;

        // Game parameters
        static const short int SCREEN_WIDTH = 350;
        static const short int SCREEN_HEIGHT = 625;
        static const short int PIPE_SPACE = 160;
        static const short int TOTAL_PIPE = 2;
        static const short int PIPE_DISTANCE = 220;
        static const short int LAND_HEIGHT = 150;
        static const short int PLAYER_WIDTH = 50;
        static const short int PLAYER_HEIGHT = 35;
};

class position{  
    public: 
        float x, y; 
        short int angle, state;
        void getPos(const short int x, const short int y); 
}; 

#endif
