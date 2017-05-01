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

    
/* ########## IMAGE ######## */
    Image tabSquareColor[5];
    Image Background;
    
/* ######### GAME ######### */
    PartitionMaker* partMaker;
    TTF_Font * font;
    Mix_Music *music;
    
    
    bool tabIsPress[5];

public :
	
    SdlPartitionMaker(SDL_Window * window, SDL_Renderer * renderer, const Song& song, unsigned int difficulty);

    ~SdlPartitionMaker();

    void backgroundImageLoad();
    
    void sdlLoop();

    void sdlShow(string line);
    void sdlShowDiff();
    void sdlShowTime(int time);
    void SdlShowSquare(unsigned int i);
};

#endif //SDL_PARTMAKER_H
