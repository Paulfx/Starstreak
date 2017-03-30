
#include "sdlGame.h"



sdlGame::sdlGame(){
    
}


sdlGame::~sdlGame(){
    
}




void sdlGame::init_Window(){
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }

}

void sdlGame::open_Window(){
        	window = SDL_CreateWindow("StarStreak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,100,100, SDL_WINDOW_SHOWN);
}




/* void sdlGame (){

}
*/
