#include "cadre.h"
#include <cassert>

const float DURATION_FRAME = 16; //en ms


/*-------------CLASSE NOTE-------------*/

Note::Note() {}

Note::Note(int x, int y, int c, bool longBool) {
	posX = x;
	posY = y;
	color = c;
	longDuration = longBool;
}

int Note::getPosX() const { return posX;}
int Note::getPosY() const { return posY;}
int Note::getColor() const { return color;}
void Note::scroll(int movement) {posY+=movement;}

/*-------------CLASSE CADRE-------------*/

Cadre::Cadre() {}

Cadre::Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, int speed, int initY, int beginV, int endV){
	tabPos[0] = pos0; 
	tabPos[1] = pos1;
	tabPos[2] = pos2;
	tabPos[3] = pos3;
	tabPos[4] = pos4;
	cspeed = speed;
	initialY = initY;
	beginningValid = beginV;
	endValid = endV;
	//partition = currPart;

	movingY = (endValid - initY) / (cspeed / DURATION_FRAME); //qtité de déplacement pour déplacer en cspeed milliseconds la note
															//jusqu'à la fin du cadre
}

bool Cadre::update(uint32_t time, line* currLine) {
	cout<<currLine->time<<endl<<time<<endl;

	assert(currLine->time > time);
	bool ajout=false;

	//On fait avancer les notes existantes
	scrollCadre();

	//Ajout de la ligne, si c'est le moment
	float actualTime = currLine->time - time;
	Note* note;

	if( actualTime < (cspeed + DURATION_FRAME) && actualTime > (cspeed - DURATION_FRAME) ) {
		//On ajoute les notes de la ligne au cadre
		ajout=true;
		for(unsigned int i=0;i<5;++i){
			if(currLine->data[i] == '1') { note= new Note(tabPos[i],initialY,i,false);noteTab.push_back(note); }
			else if(currLine->data[i] == '2') { note = new Note(tabPos[i],initialY,i,true);noteTab.push_back(note); }
			
		}

	}
	return ajout;
}


void Cadre::scrollCadre() {
	Note* tmpNote;
	for(unsigned int i=0;i<noteTab.size();++i) {
		noteTab[i]->scroll(movingY);
		if(noteTab[i]->getPosY() > endValid) { //La note n'est plus dans le cadre, on l'efface
			tmpNote = noteTab[i];
			noteTab.erase(noteTab.begin() + i);
			delete tmpNote;
		}
	}
}

int Cadre::getNbNote() const { return noteTab.size();}

Note* Cadre::getPtrNote(int i) { 
	assert(i<noteTab.size());
	return noteTab[i];
}

bool Cadre::isEmpty() const { return noteTab.empty();}
