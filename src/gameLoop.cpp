#include"gameLoop.h"
#include<iostream>

void game::takeInput(){
    while ( SDL_PollEvent(&event) != 0 ){
        if ( event.type == SDL_QUIT ){
            userInput.Type = input::QUIT;
            quit = true; 
        }
    }
}

game::game(){
    initGraphic(); 
}

game::~game(){
    free(); 
    releaseGraphic(); 
}

bool game::initGraphic(){
    bool success = true; 

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else{
		if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow( "Flappy Doge", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if ( gWindow == NULL ){
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if ( gRenderer == NULL ){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & imgFlags ) ){
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void game::display(){
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer); 
}

void game::releaseGraphic(){
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_Quit(); 
    IMG_Quit(); 
}

void game::renderBackground(){
    LTexture image;
    image.Load("res/img/background.png", 1); 
    image.Render(0, 0);
    image.free(); 
}

void game::renderLand(){
	LTexture image;
	image.Load("res/image/land.png", 1);
	image.Render(SCREEN_WIDTH - image.getWidth(), SCREEN_HEIGHT - image.getHeight()); 
	image.free(); 
}

void game::renderMessage(){
	LTexture image;
	image.Load("res/image/message.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.free(); 
}

void game::resume(){
	LTexture image;
	image.Load("res/image/resume.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free(); 
}

void game::pause(){
	LTexture image;
	image.Load("res/image/pause.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();  
}

void game::renderPauseTab(){
	LTexture image;
	image.Load("res/image/pauseTab.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230); 
	image.free(); 
}

void game::renderScoreSmall(){
	string s = to_string(score);
	short int len = s.length(); 
	LTexture image;
	
	for (short int i = len - 1; i >= 0; i --){
		string path = "res/number/small/" + string(1, s[i]) + ".png"; 
		image.Load(path.c_str(), scaleNum); 
	}
	image.free(); 
}

void game::renderScoreBig(){
	string s = to_string(score);
	short int len = s.length(); 
	LTexture image;
	
	for (short int i = len - 1; i >= 0; i --){
		string path = "res/number/large/" + string(1, s[i]) + ".png"; 
		image.Load(path.c_str(), scaleNum); 
	}
	image.free(); 
}

void game::renderBestScore(){
	ifstream bestScoreIn("res/data/bestScore.txt");
	bestScoreIn >> bestScore;
	ofstream bestScoreout("res/data/bestScore.txt"); 

	bestScore = max(bestScore, score); 
	
	string s = to_string(bestScore);
	short int len = s.length(); 
	LTexture image;

	for (short int i = len - 1; i >= 0; i --){
		string path = "res/number/small/" + string(1, s[i]) + ".png"; 
		image.Load(path.c_str(), scaleNum); 
	}
	image.free(); 

	bestScoreout << bestScore;
	bestScoreIn.close(); 
	bestScoreout.close(); 
}