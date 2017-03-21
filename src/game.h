#ifndef PARTIE_H
#define PARTIE_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <partition.h>
#include <jeu.h>
#include <score.h>

/**
 @brief la classe Partie permet d'initialiser et de gerer un partie en fonction de la partition
 */
class Partie {
    
private:
    
    Partition part;
    float score;
    int noteStreak;
    bool starPower;
    //int rockometer-valeur qui augmente (respct:baisse) lorsque qu'une note est réussie (respct:ratée). A zéro la partie s'arrête   
    
    
    
public:
    
    /** 
     @brief Constructeur par defaut
     Constructeur sans paramètres, initialise la partie sans note
     */
    Partie();
    
    /**
     @brief constructeur par paramètres
     Constructeur avec l'ensemble des arguments passés par jeu. Le constructeur de partie appelle le constructeur de partition.
     les autres valeurs sont initialisées à 0.
     @param filename reference sur le fichier de lecture/ecriture
     @param difficulty difficulté de la partie et donc modification de la lecture/ecriture sur le fichier ? 
     @todo
     */
    Partie(const string & filename,int difficulty);
    
    /**@brief Destructeur
     */
    ~Partie();
    
    
    
};
    
#endif
