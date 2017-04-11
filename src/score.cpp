#include "score.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <stdbool.h>

using namespace std;

const int VALUE_NOTE = 50;
const int ROCKMETER_MAX = 40;


Score::Score(){
    totalScore=0;
    noteStreak=0;
    starPower=0;//1 quand straPower actif
    numberSucces=0;
    numberNotes=0;
    multiplier=1;
    rockmeter=20;
}

Score::Score(const int nbNotes){
    totalScore=0;
    noteStreak=0;
    starPower=0;
    numberSucces=0;
    numberNotes=nbNotes;
    multiplier=1;
    rockmeter=20;
}

Score::~Score(){
}

void Score::updateScore(const line currLine,const Keyboard& keyState,bool fail) {
    assert(numberSucces<numberNotes);
    assert(multiplier<=4);
    assert(rockmeter<=40);
    assert(rockmeter>0); //si = -1 ou 0 la partie aurait dû s'arreter
    assert(fail==true);

    /*
     test de validité en fonction de l'état du clavier et de la ligne courante
     */
    bool testSucces=0;

    if (keyState.isValid()) { //Si la touche validation est pressée, on teste la ligne, sinon testSucces reste à false
        
        string seqUSER;
        /*convertion du tab bool en string pour la comparer avec la ligne de jeu courante*/
        for (int i=0;i<5;++i){//5 touches, 5 indices
            if (keyState.isNoPress(i)){
                seqUSER+="0";
            }
            else if (keyState.isSimplePress(i)) {
                seqUSER+="1";
            }
            else if (keyState.isLongPress(i)) {
                seqUSER+="2";
            } 
        }
        if (seqUSER == currLine.data){
            testSucces=1;
        }
    }
    
    /*gestion du strapower*/
    
    /*
     idée:-donnée membre à rajouter:Bool lastOnSequence/int accumulateurStarPower/int longueur sequence
     
     bool lastOnSequence qui permet de savoir de détecté la fin d'une séquence. Si c'est le cas on compare notestreak>=longueurSequence)
    */
  /*   if (currLine.onSequence==1){
        
    
    }*/
    if (testSucces) {
        noteStreak++;
        numberSucces++;
        if (noteStreak%10 == 0 && noteStreak<40){//de 0 à 40 notes consécutives le multiplicateur est incrémenté toutes les 10 notes
            multiplier++;
        }
        if (rockmeter<ROCKMETER_MAX){
            rockmeter++;
        }
        totalScore = totalScore + VALUE_NOTE*multiplier;
    }
    else{
        noteStreak=0;
        multiplier=1;
        rockmeter-=2;
    }
    
    if (rockmeter<=0){
        fail=false;
    }
    
}

bool Score::isFail() {
    return fail;
}
