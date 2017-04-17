
#include "cadre.h"

const float DURATION_FRAME = 0.016;

Cadre::Cadre() {}

Cadre::Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, int speed, const Partition& currPart){
	tabPos[0] = pos0; 
	tabPos[1] = pos1;
	tabPos[2] = pos2;
	tabPos[3] = pos3;
	tabPos[4] = pos4;
	cspeed = speed;
	partition = currPart;
}

void Cadre::update(uint32_t time) {

	//Ajout de la ligne, si c'est le moment

	Line currLine = partition.getLine();

	assert(currLine.time > time);

	float actualSpeed = currLine.time - time;

	if( actualSpeed < (cspeed + DURATION_FRAME) && actualSpeed < (cspeed + DURATION_FRAME) ) {
		//On doit afficher la ligne

		for(unsigned int i=0;i<5;++i){
			if(currLine.data[i] == "1") {
				Note note(tabPos[i],0,i);
				noteTab.push_back(note);
			}
		}

	}

	//On fait avancer les notes existantes

	for(unsigned int i=0;i<noteTab.size();++i) {

	}

}


// actualspeed = 2000 cspeed = 2000 