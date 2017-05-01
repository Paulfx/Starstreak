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

/** 
 @Brief Classe de gestion de la partie, comprend l'affichage et les appels sur les differentes fonctionnalitées du Core
 */
class SdlGame {

private :
	
/* ######### FENETRE ######### */
    SDL_Window * window;
    SDL_Renderer * renderer;
    int width,height; //taille de la fenêtre

/* ######### GAME ######### */
    Game* game;
    Image im_note0, im_note1, im_note2, im_note3, im_note4,im_noteAlredyPlayed; //Acces par switch
    Image Background; //Image de fond
    Image backgroundCalque; //Calque de fond
    Image tabImV [5]; //acces avec un for
    Image tabImVPush [5]; //acces avec un for
    
    
    Mix_Music *music; //Musique en cours

    bool tabPush [5]; //tabPush[i] est true tant que la touche n'est pas relaché
    bool leavebyQ; //Booleen de fermeture permet le bon affichage du commentaire de fin de partie
    
    SDL_Texture* texScore; //Texture de travail pour le score
    TTF_Font * font; //Police d'affichage

   
    
public :
	
	SdlGame();

	/** @brief Constructeur par paramètres
    @param Fenetre du jeux
     @param Renderer
     @param[in, out] song Chanson en cours
     @param difficulty Difficulté en cours
     */
    SdlGame(SDL_Window * window, SDL_Renderer * renderer, const Song& song,unsigned int difficulty);
    
    /** @brief Destructeur
     */
    ~SdlGame ();

    /** @brief Boucle principale du jeux.
        Contient des appels aux autres boucles d'affichage et de gestion et les tests d'events SDL
     */
    void sdlLoop();
    /** @brief  Affichage principal du jeux.
        Contient des appels aux fonctions de affichages mineurs
     */
    void sdlShow();

    /** @brief Affichage mineur
        Affiche la barre de validation
     */
    void drawValidation();
    
    /** @brief Affichage mineur
        Affiche l'image de fond (spécifique à chaque sound) et le calque
     */
    void backgroundImageLoad();
    
    /** @brief Fonction mineure
     @param[in,out] Surface liberée aprés usage
     @return Pointeur sur Texture
     */
    SDL_Texture* surfaceToTexture( SDL_Surface* surf );
    
    /** @brief Fonction d'affichage
     Affiche le score, la streak, le multiplier et le rockmeter
     */
    void sdlScore();
    
    /** @brief Affiche le score final avec un delay de 4 sec
     */
    void sdlShowEnd();
};

#endif //SDL_GAME_H
