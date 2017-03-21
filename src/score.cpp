#include "score.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <fstream>

using namespace std;

const int VALUE_NOTE = 50;

Score::Score(){
    totalScore=0;
    noteStreak=0;
    starPower=0;
    numberSucces=0;
    numberNotes=0;
    multiplier=1;
}

Score::Score(const int nbNotes){
    totalScore=0;
    noteStreak=0;
    starPower=0;
    numberSucces=0;
    numberNotes=nbNotes;
    multiplier=1;
}

Score::~Score(){
}

void Score::updateScore(const line currLine,const Keyboard keyState){
    
    /*
     test de validité en fonction de l'état du clavier et de la ligne courante
     */
    bool TEST_SUCCES=0;
    
    bool tab[6] = keyState.getTab();
    string seqUSER; //contient les touches appuyées par l'user sous la forme d'une chaine de caractère
    
    /*convertion du tab bool en string pour la comparer avec la ligne de jeu courante*/
    
    for (int i=1;i<=5;++i){//la boucle commence à 1 car la 1ere case du tab correspond à la touche "enter" (elle n'apparait dpnc pas dans Line
        if (tab[i]==TRUE){
            seqUSER+="1";
        }
        else seqUSER+="0";
    }
    if (seqUSER == currLine){
        TEST_SUCCES=1;
    }
    
    if (TEST_SUCCES) {
        noteStreak++;
        numberSucces++;
        if (noteStreak%10 == 0 && noteStreak<40){//de 0 à 40 notes consécutives le multiplicateur est incrémenté toutes les 10 notes
            multiplier++;
        }
        totalScore = totalScore + VALUE_NOTE*multiplier;
    }
    else{
        noteStreak=0;
        multiplier=1;
    }
    
}
