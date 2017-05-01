#include <SDL2/SDL_image.h>

#include "sdlClass.h"


#include <iostream>
#include <cassert>

using namespace std;

// ============= IMAGE =============== //

Image::Image () {
    texture = NULL;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    SDL_Surface* surface;
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        exit(1);
    }
    
    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    width=surfaceCorrectPixelFormat->w;
    height=surfaceCorrectPixelFormat->h;
    texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    SDL_FreeSurface(surfaceCorrectPixelFormat);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?width:w;
    r.h = (h<0)?height:h; 
    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
}
