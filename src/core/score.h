#ifndef SCORE_H
#define SCORE_H

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>


#include "partition.h"
#include "keyboard.h"
#include "class.h"

class Score {
/**
 @brief La classe score contient toutes les données utiles à la gestion de l'évaluation d'une partie
*/
    
private :
    
    int totalScore;
    int noteStreak;
    bool starPower;
    int numberSuccess;
    int numberNotes;
    unsigned int multiplier; //valeur (de 1 à 4) établit en fonction de noteStreak qui multiplie la valeur d'une note
    int rockmeter; /*la valeur augmente (respct:baisse) lorsque qu'une note est réussie (respct:ratée). A zéro (ou -1) la partie s'arrête*/
    bool fail=false; //True si le joueur a perdu


public:
    
    /** 
     @brief Constructeur par défaut 
     Constructeur sans paramètres, initialise toutes les valeurs à 0
     */
    Score();
    
    /**
     @brief Constructeur par paramètres
     Ce constructeur permet d'initialiser le nombre de notes total afin d'avoir un pourcentage de notes réussites
     */
    Score(const int nbNotes);
    
    /**
     @brief Destructeur
     */
    ~Score();
    
    /**
     @brief La fonction updateScore est appelée à chaque fois qu'une note doit etre jouée. Elle contient un test de validité qui compare la ligne de jeu courante avec l'état du clavier.
      Les différentes valeurs du score seront ensuite mises à jour en fonction du résultat de ce test.
     */
    void updateScore(const line currLine,const Keyboard& keyState);

    bool isFail();

    void update(const vector<Note*>& tabNeedPlay, Keyboard& keyboard);

    void success();

    void failure();

    int getTotalScore() const;
    int getNoteStreak() const;
    int getNumberSuccess() const;
    unsigned int getMultiplier() const;
    int getRockmeter() const;
    bool getFailed() const;

};
#endif
