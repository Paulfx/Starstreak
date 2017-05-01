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
 @brief Classe gerant l'affichage et la gestion du menu
 */
class SdlMenu {
    
private :
    
/* ######### FENETRE ######### */

    SDL_Window * window;
    SDL_Renderer * renderer;
    int height,width; //Taille de la fenêtre
    
    
    
    
/* ######### MENU ######### */
    TTF_Font * fontMenu; //Police pour le menu
    Menu* menu;

/* ######### TEXTURES ######### */
    vector<SDL_Texture*> texTab; //Contient les textures de texte des chansons
    SDL_Texture* textureDiff0; //Contient les textures de texte pour les difficultés
    SDL_Texture* textureDiff1;
    SDL_Texture* textureDiff2;

    //SdlGame game;
    
    int posPtr; //Position du pointeur ecran (!=pointeur du Core->selection des chansons)
    
    
    int stateMenu; //Etat du menu
    // Etat du menu :
    //par default on est dans le premier (0)
    //1 -> Selection chanson
    //2 -> Difficulté
    //3 -> Creation (Bouton non cliquable)
    
    bool creationMode; //Mode jouer/creer
    string choosenSongTitle; //Titre de la chanson selectionnée
    
    Image im_backgroundMenu0; //BackgroundMenu0 + Calque
    Image im_backgroundMenu1; //BackgroundMenu1 + Calque
    Image im_backgroundMenu2; //BackgroundMenu2 + Calque
    Image im_ptrMenu; //Image pointeurMenu (Select)
    Image im_ptrMenuWhite; //Image pointeur menu 0
    Image im_ptrMenuBlack; //Image pointeur menu 0

/* son */
    Mix_Chunk *soundMove; //Son de deplacement dans le menu
    Mix_Chunk *soundAccept; //Son correspondant a la touche entrée dans le menu
    Mix_Chunk *soundBack; //Son correspondant a la touche echap
    Mix_Chunk *soundMenu; //Musique du menu
    
public :
    
    /** @brief Constructeur par default
     */
    SdlMenu ();
    
    /** @brief Destructeur
     */
    ~SdlMenu ();
    
    /** @brief Initialise les images
     */
    void sdlInit();

    /** @brief
     */
    void createTextTextures();

    /** @brief
     */
    SDL_Texture* surfaceToTexture(SDL_Surface* surf);
    
    /** @brief Fonction d'affichage mineure
        appel aux boucles mineures et a la boucle d'affichage
     */
    void sdlLoop();
    
    /** @brief  Fonction d'affichage principale
        appel aux fonctions mineures d'affichages
     */
    void sdlShow();
    
    /** @brief Fonction d'affichage mineure
        affiche les difficultés disponibles
     */
    void sdlShowDiff();
    
    /** @brief Fonction d'affichage mineure
        affiche le menu deroulant et les differentes musiques disponibles
     */
    void sdlShowSelect();
    
    /** @brief Fonction d'affichage mineure
        affiche le menu initial
     */
    void sdlShowMenu();
    
    /** @brief Boucle mineure du menu
        Boucle d'evenement sur le menu du choix de difficulté
     */
    int sdlLoopDiff();
    
    /** @brief Boucle mineure du menu
        boucle d'evenement sur le menu du choix de la musique
     */
    int sdlLoopSelect();
    
    /** @brief Boucle mineure du menu
        boucle d'evement sur le menu initial
     */
    int sdlLoopMenu();
    
    /** @brief Initialise de la lecture des fichiers sons
     */
    void soundInit();
    
    /** @brief Destructeur du son
        libere les sons
     */
    void soundQuit();
    
    /** @brief Fonction de deplacement du pointeur ecran
        @param move deplacement du pointeur
        @IDmenu IDmenu utile pour la taille du retour en haut
        @nbDiff Nombre de difficulté possible (fixé à 3)
     */
    void movePtr(const string move,const int IDmenu,const int nbDiff);
    
};

#endif

 /* sdlMenu_h */
