#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <stdint.h>

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
    vector<string> cadre; //Contient le cadre
    

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
    
    /**@brief fonction qui traite les lignes dans la file en fonction du temps
     */
    void exeGame ();//peut etre inutile
    
    bool isFail();

    vector<string> getCadre() const;

    Song getSong() const;

    Score getScore() const;

    void defileCadre(uint32_t time);
    
};
    
#endif
