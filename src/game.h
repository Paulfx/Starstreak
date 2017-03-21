#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>

#include <partition.h>
#include <score.h>

/**
 @class Game 
 @brief Classe qui gère une partie
 */
class Game {
    
private:
    
    Partition part;
    Score score;
    bool creationMode;

    //int rockometer-valeur qui augmente (respct:baisse) lorsque qu'une note est réussie (respct:ratée). A zéro la Game s'arrête   
    
    
    
public:
    
    /** 
     @brief Constructeur par defaut
     Constructeur sans paramètres, initialise la Game sans note
     */
    Game();
    
    /**
     @brief constructeur par paramètres
     Constructeur avec l'ensemble des arguments passés par jeu. Le constructeur de Game appelle le constructeur de partition.
     les autres valeurs sont initialisées à 0.
     @param filename reference sur le fichier de lecture/ecriture
     @param difficulty difficulté de la Game et donc modification de la lecture/ecriture sur le fichier ? 
     @todo
     */
    Game(const string & filename,int difficulty);
    
    /**@brief Destructeur
     */
    ~Game();
    
    
    
};
    
#endif