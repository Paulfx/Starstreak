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
    SDL_Texture * texture;
    SDL_Window * window;
    SDL_Renderer * renderer;
    int width,height; //taille de la fenêtre

/* ######### GAME ######### */
    string titleSong;
    Game* game;

    Image im_note0, im_note1, im_note2, im_note3, im_note4, im_ligneValidation;

public :
	
	SdlGame();

	/** @brief Constructeur
     */
    SdlGame(SDL_Texture * texture, SDL_Window * window, SDL_Renderer * renderer, const Song& song,unsigned int difficulty,bool mode);
    
    /** @brief Destructeur
     */
    ~SdlGame ();

    /** @brief Mouvement en interaction du jeux
     */
    void sdlLoop();
    /** @brief  Affichage de l'etat actuel du jeux 
     */
    void sdlShow();
    

};

#endif //SDL_GAME_H
