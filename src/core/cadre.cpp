#include "cadre.h"
#include <cassert>
#include <iostream>

const float DURATION_FRAME = 16; //en ms


Cadre::Cadre() {}

Cadre::Cadre(unsigned int pos0,unsigned int pos1,unsigned int pos2,unsigned int pos3,unsigned int pos4, float time, unsigned int initY, unsigned int beginV, unsigned int endV){
	tabPos[0] = pos0; 
	tabPos[1] = pos1;
	tabPos[2] = pos2;
	tabPos[3] = pos3;
	tabPos[4] = pos4;
	timeUntil = time; //Temps en secondes
	initialY = initY;
	beginValid = beginV;
	endValid = endV;
	totalTime = 0.f;

	speed=(float)(beginValid + (float)(endValid-beginValid)/2 - initialY)/timeUntil;//En pixels par seconde
	assert(speed!=0);
	timeLine=0;
}


Cadre::~Cadre(){
	for(unsigned int i=0;i<noteTab.size();++i) delete noteTab[i];  //Normalement, le tableau est vide et désalloué
}

/*
delta représente le temps depuis le dernier appel de la fonction en SECONDES
*/
bool Cadre::update(float delta, const line& currLine) {
	float timeUntilPlay;
	totalTime+=delta;
	if (timeLine == 0) timeLine = currLine.time/1000.f; //Initialisation et si la ligne précédente a été ajoutée
	timeUntilPlay=timeLine-totalTime;
	std::cout<<timeUntilPlay<<std::endl;
	std::cout<<totalTime<<std::endl;
	std::cout<<delta<<std::endl<<std::endl;
	assert(timeUntilPlay>timeUntil-delta);
	assert(timeUntil-delta>0);
	Note* note;
	bool ajout=false;
	//Ajout de la ligne, si c'est le moment
	if( timeUntilPlay < (timeUntil + delta) ) {
		//On ajoute les notes de la ligne au cadre
		ajout=true;
		timeLine=0; //On réinitialise timeLine
		for(unsigned int i=0;i<5;++i){
			if(currLine.data[i] == '1') { 
				note= new Note(tabPos[i],initialY,i,false,speed);
				noteTab.push_back(note); 
			}
			else if(currLine.data[i] == '2') { 
				note = new Note(tabPos[i],initialY,i,true,speed);
				noteTab.push_back(note); 
			}
		}
	}
	return ajout;
}


void Cadre::scrollCadre(float delta, Score& score) {
	Note* tmpNote;
	unsigned int posY;
	for(unsigned int i=0;i<noteTab.size();++i) {
		noteTab[i]->scroll(delta);
		posY = noteTab[i]->getPosY();
		if(posY >= beginValid && posY <=endValid) {
			noteTab[i]->setNeedPlay(); //La note doit être jouée
			std::cout<<"NOTE COLONNE : "<<noteTab[i]->getColor()<<" doit être jouée"<<std::endl;
		}
		else if(posY > endValid) { //La note n'est plus dans le cadre, on l'efface
			tmpNote = noteTab[i];
			noteTab.erase(noteTab.begin() + i);
			//Juste avant la suppression, si la note n'a pas été jouée, alors on appelle score.failure()
			if(!tmpNote->isPlayed()) score.failure();
			else score.success();

			delete tmpNote;//toutes les notes devraient être supprimées
		}
	}
}

unsigned int Cadre::getNbNote() const { return noteTab.size();}

Note& Cadre::getNote(unsigned int i) { 
	assert(i<noteTab.size());
	return *noteTab[i];
}

Note* Cadre::getPtrNote(unsigned int i) {
	assert(i<noteTab.size());
	return noteTab[i];
}

bool Cadre::isEmpty() const { return noteTab.empty();}

int Cadre::getBeginValid() const { return beginValid;}

int Cadre::getTabPos(unsigned int i) const { return tabPos[i];}
