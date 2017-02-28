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
 @brief la classe Partie permet de d'initialiser et de gerer un partie en fonction de la partition
 */
class Partie {
    
private:
    
    Partition part;
    float score;
    int noteStreak;
    bool starPower;
    
    
    
public:
    /** 
     @brief Constructeur par defaut
     Constructeur sans paramètres, initialise la partie sans note
     */
    Partie();
    /**
     @brief constructeur par paramètres
     Constructeur avec l'ensemble des arguments passés par jeu
     */
    Partie(
    
    
};
