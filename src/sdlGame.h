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

    Mix_Music *music;

    Image im_note0, im_note1, im_note2, im_note3, im_note4, im_ligneValidation,
    im_noteV0, im_noteV1, im_noteV2, im_noteV3, im_noteV4/*note val et val pull*/, im_noteVPush0, im_noteVPush1, im_noteVPush2, im_noteVPush3, im_noteVPush4;

    Image tabImV [5];
    Image tabImVPush [5];

public :
	
	SdlGame();

	/** @brief Constructeur
     */
    SdlGame(SDL_Window * window, SDL_Renderer * renderer, const Song& song,unsigned int difficulty,bool mode);
    
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
    

};

#endif //SDL_GAME_H
