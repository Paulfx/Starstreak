#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <queue>

#include "partition.h"
#include "struct.h"
#include "score.h"

/**
 @class Game 
 @brief Classe qui contient les informations d'une partie (la chanson en cours, la partition associée, le score).
 S'occupe du cadre déroulant des notes.
 */
class Game {
    
private :
    
    Partition partition;
    Score score;
    bool creationMode;
    Song song;
    queue<line> cadre; //Contient le cadre
    bool fail; //True si le joueur a perdu

    //int rockometer-valeur qui augmente (respct:baisse) lorsque qu'une note est réussie (respct:ratée). A zéro la Game s'arrête   
    
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
    Game(Song* song,unsigned int difficulty);
    
    /**@brief Destructeur
     */
    ~Game();
    
    bool isFail();
    
};
    
#endif
