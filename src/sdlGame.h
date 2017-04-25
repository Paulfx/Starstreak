#ifndef sdlGame_hpp
#define sdlGame_hpp

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#include <stdio.h>
#include <stdlib.h> 
#include <cassert>
#include <iostream>
#include "menu.h"

using namespace std;

class Image {
    
private:
    
    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;
    
public:
    Image () ;
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
};



/**
 La classe gÈrant le jeu avec un affichage SDL
 */
class sdlGame {
    
    private :
    
    
    SDL_Texture * texture;
    SDL_Window * window;
    SDL_Renderer * renderer;
    TTF_Font * fontMenu; //Police pour le menu
    //SDL_Mixer * ????
    //SDL_DisplayMode currentMode; //currentMode : structure contenant taille de l'écran : w (width) et h (height)
    Menu* menu;
    
    int height,width;

    Image im_background;
    

    
    public :
    
    
    
    /** @brief Constructeur
     */
    sdlGame ();
    
    /** @brief Destructeur
     */
    ~sdlGame ();
    
    
    //SDL_Texture* surfaceNote(SDL_Renderer * renderer,int i);
    
    void sdlMenuLoop();
    void sdlShowMenu ();
    
    void sdlGameLoop ();
    void sdlShowGame();
    
    void sdlTest();
    
};

#endif

 /* sdlGame_hpp */
