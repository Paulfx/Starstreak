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
    
    int totalScore; //Score total de la parti en cours
    int noteStreak; //Serie de notes reussies
    int numberSuccess; //Nombre de note reussies
    int numberNotes; //nombre de notes
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
     @param const int nbNotes Valeur récupérée dans le fichier index.
     */
    Score(const int nbNotes);
    
    /**
     @brief Destructeur
     */
    ~Score();
    
    /**
     @brief La fonction updateScore est appelée à chaque fois qu'une note doit etre jouée. Elle contient un test de validité qui compare la ligne de jeu courante avec l'état du clavier.
     Les différentes valeurs du score seront ensuite mises à jour en fonction du résultat de ce test.
     @param[const in] tabNeedPlay vector contenant la ligne de note à jouer
     @param[in, out] Keyboard contient la ligne de touches utilisateur, l'etat est modifié pour eviter de jouer deux fois la même note
     */
    void update(const vector<Note*>& tabNeedPlay, Keyboard& keyboard);

    /** @brief Incrémentation des valeurs du score.
     */
    void success();

    /** @brief Décrémentation des valeurs du score.
     */
    void failure();

    /** @brief Accesseur score
     @return int
     */
    int getTotalScore() const;
    
    /** @brief Accesseur série de notes
     @return int
     */
    int getNoteStreak() const;
    
    /** @brief Accesseur nombre de notes réussies
     @return unsigned int
     */
    int getNumberSuccess() const;
    
    /** @brief Accesseur multiplicateur
     @return unsigned int
     */
    unsigned int getMultiplier() const;
    
    /** @brief Accesseur rockmeter (equivalent à une barre de vie)
     @return int
     */
    int getRockmeter() const;
    
    /** @brief Cette fonction renvoit true si la partie est perdue.
     @return bool
     */
    bool getFailed() const;

};
#endif
