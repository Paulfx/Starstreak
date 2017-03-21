#ifndef SCORE_H
#define SCORE_H


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>




class Score {
/**
 @brief La classe score contient toutes les données utiles à la gestion de l'évaluation d'une partie
*/
    
private :
    
    int totalScore;
    int noteStreak;
    bool starPower;
    int numberSucces;
    int numberNotes;
    unsigned int multiplier; //valeur (de 1 à 4) établit en fonction de noteStreak qui multi la valeur d'une note
    //int rockometer-valeur qui augmente (respct:baisse) lorsque qu'une note est réussie (respct:ratée). A zéro la partie s'arrête
    
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
     @brief La fonction updateScore est appelée à chaque fois qu'une note doit etre jouée. Elle contient un test de validité qui compare la ligne de jeu courante avec létat du clavier. Les différentes valeurs du score seront ensuite mise à jour en fonction du résultat du ce test.
     */
    void updateScore(const line currLine,const Keyboard keyState);
    

}

#endif
