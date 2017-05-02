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
    numberSuccess=0;
    numberNotes=0;
    multiplier=1;
    rockmeter=20;
}

Score::Score(const int nbNotes){
    totalScore=0;
    noteStreak=0;
    numberSuccess=0;
    numberNotes=nbNotes;
    multiplier=1;
    rockmeter=20;
}

Score::~Score(){
}


void Score::update(const vector<Note*>& tabNeedPlay, Keyboard& keyboard) {
    unsigned int i,j;
    bool play = false;
    for(i=0;i<5;++i) { //i<keyboard.nbNote ==> dépend de la difficulté ?
        //Si une note doit être jouée
        for(j=0;j<tabNeedPlay.size();++j){ //Pour toutes les notes jouables
            if(tabNeedPlay[j]->getColor() == i) { //La note est dans la bonne colonne
                play=true;
                if(keyboard.isSimplePress(i) || keyboard.isLongPress(i)) {//Appui simple
                    tabNeedPlay[j]->setPlayed();
                    keyboard.setNoPress(i);
                    cout<<"NOTE COLONNE : "<<j<<" est jouée"<<endl;
                    //success();
                }
            }  
        }
        //Sinon, si aucune note ne doit être jouée
        if(!play) {
            if(!keyboard.isNoPress(i)) {
                failure(); //Si le joueur a apppuyé, echec
                keyboard.setNoPress(i);
                cout<<"TOUCHES SANS NOTES"<<endl;
            }
        }
        play=false;
    }

}




void Score::success() {
cout<<"SUCCESS"<<endl;

    noteStreak++;
    numberSuccess++;
    if (noteStreak%10 == 0 && noteStreak<40){//de 0 à 40 notes consécutives le multiplicateur est incrémenté toutes les 10 notes
        multiplier++;
    }
    if (rockmeter<ROCKMETER_MAX){
        rockmeter++;
    }
    totalScore = totalScore + VALUE_NOTE*multiplier;
}

void Score::failure() {
cout<<"FAIL"<<endl;
    noteStreak=0;
    multiplier=1;
    rockmeter-=2;
    if (rockmeter<-30){
        fail=true;
    }
}

int Score::getTotalScore() const{return totalScore;}
int Score::getNoteStreak() const{return noteStreak;}
int Score::getNumberSuccess() const{return numberSuccess;}
unsigned int Score::getMultiplier() const{return multiplier;}
int Score::getRockmeter() const{return rockmeter;}
bool Score::getFailed() const{return fail;}
