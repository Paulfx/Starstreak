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
    Image BackgroundCalque;
    
/* ######### GAME ######### */
    PartitionMaker* partMaker;
    TTF_Font * font;
    Mix_Music *music;
    
    string oldLine; //Permet de se souvenir de la ligne d'avant
    

public :
	
    SdlPartitionMaker(SDL_Window * window, SDL_Renderer * renderer, const Song& song, unsigned int difficulty);

    ~SdlPartitionMaker();

    void backgroundImageLoad();
    
    void sdlLoop();

    void sdlShow(const string& line, int timeSeconds);
    void sdlShowLine(const string& line);
    void sdlShowDiff();
    void sdlShowTime(const int time);
};

#endif //SDL_PARTMAKER_H
