#include "score.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <stdbool.h>

using namespace std;

const int VALUE_NOTE = 50;
const int ROCKOMETER_MAX = 40;


Score::Score(){
    totalScore=0;
    noteStreak=0;
    starPower=0;
    numberSucces=0;
    numberNotes=0;
    multiplier=1;
    rockometer=20;
}

Score::Score(const int nbNotes){
    totalScore=0;
    noteStreak=0;
    starPower=0;
    numberSucces=0;
    numberNotes=nbNotes;
    multiplier=1;
    rockometer=20;
}

Score::~Score(){
}

void Score::updateScore(const line currLine,const keyboard& keyState) {
    
    assert(numberSucces<numberNotes);
    assert(multiplier<=4);
    assert(rockometer<=40);
    assert(rockometer>0); //si = -1 ou 0 la partie aurait dû s'arreter
    /*
     test de validité en fonction de l'état du clavier et de la ligne courante
     */
    bool testSucces=0;
    
    bool *tab = keyState.getKey();
    string seqUSER; //contient les touches appuyées par l'user sous la forme d'une chaine de caractère
    
    /*convertion du tab bool en string pour la comparer avec la ligne de jeu courante*/
    
    for (int i=1;i<=5;++i){//la boucle commence à 1 car la 1ere case du tab correspond à la touche "enter" (elle n'apparait dpnc pas dans Line
        if (tab[i]==true){
            seqUSER+="1";
        }
        else seqUSER+="0";
    }
    if (seqUSER == currLine.data){
        testSucces=1;
    }
    
    if (testSucces) {
        noteStreak++;
        numberSucces++;
        if (noteStreak%10 == 0 && noteStreak<40){//de 0 à 40 notes consécutives le multiplicateur est incrémenté toutes les 10 notes
            multiplier++;
        }
        if (rockometer<ROCKOMETER_MAX){
            rockometer++;
        }
        totalScore = totalScore + VALUE_NOTE*multiplier;
    }
    else{
        noteStreak=0;
        multiplier=1;
        rockometer-=2;
    }
    
    if (rockometer<=0){
        
    }
    
}
