#include"textureManager.h"
#include <iostream> 

bool LTexture::quit = 0;
bool LTexture::die = true;
short int LTexture::score = 0;
SDL_Window* LTexture::gWindow = NULL;
SDL_Renderer* LTexture::gRenderer = NULL; 
SDL_Event LTexture::event; 

LTexture::LTexture(){
    Texture = NULL;
}

short int LTexture::getWidth(){
    return tWidth;
}

short int LTexture::getHeight(){ 
    return tHeight;
}

void LTexture::Render(short int x, short int y, short int angle, SDL_Rect* srcrect, SDL_RendererFlip flip){
	SDL_Rect dstrect = {x, y, tWidth, tHeight};

    if( srcrect != NULL )
	{
		dstrect.w = srcrect->w;
		dstrect.h = srcrect->h;
	}

    SDL_RenderCopyEx(gRenderer, Texture, srcrect, &dstrect, angle, NULL, flip);
}

bool LTexture::Load(string path, double scale){
    Free(); 

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if ( loadedSurface == NULL ){
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));
        Texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); 
        if ( Texture == NULL ){
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else{
            tWidth = (loadedSurface->w) * scale; 
            tHeight = (loadedSurface->h) * scale; 
        }

        SDL_FreeSurface(loadedSurface);
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return Texture != NULL; 
}

void LTexture::Free(){  
    if ( Texture != NULL ){
        SDL_DestroyTexture(Texture);
        Texture = NULL; 
        tWidth = 0;
        tHeight = 0; 
    }
}

bool LTexture::isNULL(){
    if ( Texture == NULL ) return 1;
    else return 0; 
}

void position::getPos(const short int x, const short int y){
    this->x = x;
    this->y = y; 
}
