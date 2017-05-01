#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#include <stdio.h>
#include <stdlib.h> 
#include <cassert>
#include <iostream>

#include "game.h"
#include "sdlClass.h"

using namespace std;

class SdlGame {

private :
	
/* ######### FENETRE ######### */
    SDL_Window * window;
    SDL_Renderer * renderer;
    int width,height; //taille de la fenêtre

/* ######### GAME ######### */
    Game* game;
    Image im_note0, im_note1, im_note2, im_note3, im_note4,im_noteAlredyPlayed; //Acces unique par switch
    Image Background;
    Image BackgroundCalque; //emplacement score/cadre/etc
    Image tabImV [5]; //acces avec un for
    Image tabImVPush [5]; //acces avec un for
    
    Mix_Music *music;

    bool tabPush [5]; //tabPush[i] est true tant que la touche n'est pas relaché
    
    SDL_Texture* texScore;
    TTF_Font * fontMenu;

    
public :
	
	SdlGame();

	/** @brief Constructeur
     */
    SdlGame(SDL_Window * window, SDL_Renderer * renderer, const Song& song,unsigned int difficulty);
    
    /** @brief Destructeur
     */
    ~SdlGame ();

    /** @brief 
     */
    void sdlLoop();
    /** @brief  Affichage de l'etat actuel du jeu 
     */
    void sdlShow();

    void drawValidation();
    
    void backgroundImageLoad();
    
    SDL_Texture* surfaceToTexture( SDL_Surface* surf );
    
    
    void sdlScore();
    void sdlShowEnd();
};

#endif //SDL_GAME_H
