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

    
    int posPtr;
    int stateMenu;
    // Etat du menu :
        //par default on est dans le premier (0)
        //1 -> Selection chanson
        //2 -> Difficulté
        //3 -> Creation (Bouton non cliquable)
    
    /* ######### IMAGE ######## */
    Image im_backgroundMenu0;
    Image im_backgroundMenu1;
    Image im_backgroundMenu2;
    Image im_ptrMenu;

    /* PARTIE GAME*/

    Image im_note0, im_note1, im_note2, im_note3, im_note4, im_ligneValidation;



    
    public :
    
    
    
    /** @brief Constructeur
     */
    sdlGame ();
    
    /** @brief Destructeur
     */
    ~sdlGame ();
    
    
    //SDL_Texture* surfaceNote(SDL_Renderer * renderer,int i);
    
    
    
    /** @brief Mouvement et appel a ShowMenu
     */
    void sdlMenuLoop();
    
    /** @brief  Affiche le menu de selection de chanson
     */
    void sdlShowMenu();
    
    /** @brief Mouvement en interaction du jeux
     */
    void sdlGameLoop();
    /** @brief  Affichage de l'etat actuel du jeux 
     */
    void sdlShowGame();
    void sdlTest();
    
    
    //fonction moove du pointeur indepandant de currI
    //Static ? modification des données private en static possible ?
    void moveUpPtr();
    void moveDownPtr();
    
};

#endif

 /* sdlGame_hpp */
