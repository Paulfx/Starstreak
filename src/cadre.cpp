#include "cadre.h"

const float DURATION_FRAME = 16; //en ms


/*-------------CLASSE NOTE-------------*/

Note::Note() {}

Note::Note(const int x, int y, int c, bool longBool) {
	posX = x;
	posY = y;
	color = c;
	longDuration = longBool;
}

const int Note::getPosX() const { return posX;}
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

	moving = (endValid - initY) / (cspeed / DURATION_FRAME); //qtité de déplacement pour déplacer en cspeed milliseconds la note
															//jusqu'à la fin du cadre
}

void Cadre::update(uint32_t time, const line& currLine) {
	assert(currLine.time > time);
	//On fait avancer les notes existantes
	for(unsigned int i=0;i<noteTab.size();++i) {
		noteTab[i]->scroll(movingY);
		if(noteTab[i]->getPosY() > endValid) { //La note n'est plus dans le cadre, on l'efface
			tmpNote = noteTab[i];
			noteTab.erase(noteTab.begin() + i);
			delete tmpNote;
		}
	}

	//Ajout de la ligne, si c'est le moment
	float actualTime = currLine.time - time;

	if( actualTime < (cspeed + DURATION_FRAME) && actualTime < (cspeed + DURATION_FRAME) ) {
		//On doit afficher la ligne
		for(unsigned int i=0;i<5;++i){
			if(currLine.data[i] == "1") { Note* note= new Note(tabPos[i],initialY,i,false); }
			else if() { Note* note = new Note(tabPos[i],initialY,i,true); }
			noteTab.push_back(note);
		}

	}

}
