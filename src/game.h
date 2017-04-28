#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <stdint.h>

#include "partition.h"
#include "struct.h"
#include "score.h"
#include "cadre.h"

/**
 @class Game 
 @brief Classe qui contient les informations d'une partie (la chanson en cours, la partition associée, le score).
 */
class Game {
    
private :
    
    Partition* partition;
    Score* score;
    bool creationMode;
    Song song;
    Cadre* cadre;

    bool ligneAjoutee;
    line currLine;
    
public :
    
    /** 
     @brief Constructeur par defaut
     Constructeur sans paramètres, initialise la Game sans note
     */
    Game();
    
    /**
     @brief constructeur par paramètres
     Constructeur avec l'ensemble des arguments passés par jeu. Le constructeur de Game appelle le constructeur de partition.
     les autres valeurs sont initialisées à 0.
     @param song pointeur sur le Song choisit
     @param difficulty difficulté de la Game et donc modification de la lecture/ecriture sur le fichier ? 
     @todo
     */
    Game(const Song& song,unsigned int difficulty,bool mode);
    
    /**@brief Destructeur
     */
    ~Game();
    
    /**@brief accesseur de l'attribut song, instance de la classe Song
    @return une référence vers song
    */
    const Song& getSong();

    /**@brief accesseur de l'attribut score, instance de la classe Score
    @return une référence vers score
    */
    Score& getScore();

    /**@brief accesseur de l'attribut partition, instance de la classe Partition
    @return une référence vers partition 
    */
    Partition& getPartition();

    /**@brief accesseur de l'attribut cadre, instance de la classe Cadre
    @return une référence vers cadre 
    */
    Cadre& getCadre();
    
    void update(float delta);
    
};
    
#endif
