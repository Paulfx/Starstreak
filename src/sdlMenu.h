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
#include "sdlClass.h" //importe classe image
#include "sdlGame.h"
#include "sdlPartitionMaker.h"

using namespace std;

/**
 La classe gÈrant le jeu avec un affichage SDL
 */
class SdlMenu {
    
private :
    
/* ######### FENETRE ######### */
    SDL_Window * window;
    SDL_Renderer * renderer;
    int height,width; //Taille de la fenêtre

/* ######### MENU ######### */
    TTF_Font * fontMenu; //Police pour le menu
    //SDL_Mixer * ????
    //SDL_DisplayMode currentMode; //currentMode : structure contenant taille de l'écran : w (width) et h (height)
    Menu* menu;


    //SdlGame game;
    
    int posPtr;
    int stateMenu;
    string choosenSongTitle;
    bool creationMode;
    // Etat du menu :
        //par default on est dans le premier (0)
        //1 -> Selection chanson
        //2 -> Difficulté
        //3 -> Creation (Bouton non cliquable)
    
    Image im_backgroundMenu0;
    Image im_backgroundMenu1;
    Image im_backgroundMenu2;
    Image im_ptrMenu;
    Image im_ptrMenuWhite;
    Image im_ptrMenuBlack;

/* son */
    Mix_Chunk *soundMove;
    Mix_Chunk *soundAccept;
    Mix_Chunk *soundMenu;
    
public :
    
    /** @brief Constructeur
     */
    SdlMenu ();
    
    /** @brief Destructeur
     */
    ~SdlMenu ();
    
    
    //SDL_Texture* surfaceNote(SDL_Renderer * renderer,int i);
    
    /** @brief Mouvement et appel a ShowMenu
     */
    void sdlLoop();
    
    /** @brief  Affiche le menu de selection de chanson
     */
    void sdlShow();
    
    void sdlTest();
    
    void soundInit();
    
    void soundQuit();
    
    //fonction moove du pointeur indepandant de currI
    //Static ? modification des données private en static possible ?
    void movePtr(const string move,const int IDmenu,const int nbDiff);
    
};

#endif

 /* sdlMenu_h */
