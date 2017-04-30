#ifndef SDL_PARTMAKER_H
#define SDL_PARTMAKER_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#include <stdio.h>
#include <stdlib.h> 
#include <cassert>
#include <iostream>

#include "partitionMaker.h"
#include "sdlClass.h"

using namespace std;

class SdlPartitionMaker {

private :
	
/* ######### FENETRE ######### */
    SDL_Window * window;
    SDL_Renderer * renderer;
    int width,height; //taille de la fenêtre

/* ######### GAME ######### */
    PartitionMaker* partMaker;
    Mix_Music *music;
    TTF_Font * font;

public :
	
    SdlPartitionMaker(SDL_Window * window, SDL_Renderer * renderer, const Song& song, unsigned int difficulty);

    ~SdlPartitionMaker();

    void sdlLoop();

    void sdlShow();
    
};

#endif //SDL_PARTMAKER_H