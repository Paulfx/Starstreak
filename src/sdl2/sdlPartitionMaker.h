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

/**
 @Brief Classe de gestion de la création d'une partition, comprend l'affichage et les appels sur les differentes fonctionnalitées du Core
 */
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
	
    /** @brief Constructeur par paramètres
     @param Fenetre du jeux
     @param Renderer
     @param[in, out] song Chanson en cours
     @param difficulty Difficulté en cours
     */
    SdlPartitionMaker(SDL_Window * window, SDL_Renderer * renderer, const Song& song, unsigned int difficulty);
    
    /** @brief Destructeur
     */
    ~SdlPartitionMaker();

    /** @brief Affichage mineur
    Affiche l'image de fond du studio et le calque
    */
    void backgroundImageLoad();
    
    /** @brief Boucle principale de création.
     Contient des appels aux autres boucles d'affichage et de gestion et les tests d'events SDL
     */
    void sdlLoop();

    /** @brief  Affichage principal de création.
     Contient des appels aux fonctions de affichages mineurs
     */
    void sdlShow(const string& line, int timeSeconds);
    
    /** @brief Affichage des notes qui sont écrit dans la partition
     */
    void sdlShowLine(const string& line);
    
    /** @brief  Affichage de la difficultée
     */
    void sdlShowDiff();
    
    /** @brief Affichage du temps
     */
    void sdlShowTime(const int time);
};

#endif //SDL_PARTMAKER_H
