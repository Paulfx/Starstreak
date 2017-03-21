#include "score.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <fstream>

using namespace std;

const int VALUE_NOTE = 50;

Score:Score(){
    totalScore=0;
    noteStreak=0;
    starPower=0;
    numberSucces=0;
    numberNotes=0;
    multiplier=1;
}

Score:Score(const int nbNotes){
    totalScore=0;
    noteStreak=0;
    starPower=0;
    numberSucces=0;
    numberNotes=nbNotes;
    multiplier=1;
}

Score:~Score(){
}

void updateScore(const line currLine,const Keyboard keyState){
    
    /*
     test de validité en fonction de l'état du clavier et de la ligne courante
     */
    
    if (TEST_SUCCES) {
        ++noteStreak;
        ++numberSucces;
        if (noteStreak%10 == 0 && noteStreak<40){//de 0 à 40 notes consécutives le multiplicateur est incrémenté toutes les 10 notes
            ++multiplier;
            
        }
    }
    
}
