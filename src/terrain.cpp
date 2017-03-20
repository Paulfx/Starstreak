#include "terrain.h"

using namespace std;

Terrain::Terrain(){
    tab=NULL;
    data=NULL;
    nbLine=0;
    }

Terrain::~Terrain(){
    
}

int getNbLine(){
    return nbLine;
}

void setnbLine(){
    nbLine++;
}

void setData (const tabNotes.partition){
    
}


void groundCreates (const partition& tabNotes){
    int deltaTime;
    bol longNote=0;
    for (int i=0;i<tabNotes.nbLine;++i){
        deltaTime=tabNotes.partition[i].time - tabNotes.partition[i-1].time; //erreur si i=0
        for (int j=0;j<deltaTime;++j){
            tab.setData(
            
        }
        
    }
    
}
