//Pour l'inclusion+makefile -> les chemins d'accées sont differents donc on doit poser une condition dans le makefile. Je pense que l'include <SDL2> est trop gros pour la precompilation, sinon pas besoin du if defined (__APPLE__) parcecequ'on mettra le meme nom dans le makefile




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
    
    Menu menu;
    
    SDL_Window * window;
    SDL_Renderer * renderer;
    TTF_Font * font;
 
    
    public :
    
    
    
    /** @brief Constructeur
     */
    sdlGame ();
    
    /** @brief Destructeur
     */
    ~sdlGame ();
    
    /** @brief Initialisation de la fenetre
     */
    void init_Window();
    
    /** @brief Ouvre la fenetre SDL
     */
    void open_Window();
    

    
    void sdlLoop ();
    void sdlShow ();
    
};

#endif

 /* sdlGame_hpp */
