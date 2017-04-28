#include "cadre.h"
#include <cassert>

const float DURATION_FRAME = 16; //en ms


Cadre::Cadre() {}

Cadre::Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, float time, int initY, int beginV, int endV){
	tabPos[0] = pos0; 
	tabPos[1] = pos1;
	tabPos[2] = pos2;
	tabPos[3] = pos3;
	tabPos[4] = pos4;
	timeUntil = time; //Temps en secondes
	initialY = initY;
	beginValid = beginV;
	endValid = endV;
	//partition = currPart;
	//movingY = (endValid - initY) / (cspeed / DURATION_FRAME); //qtité de déplacement pour déplacer en cspeed milliseconds la note
															//jusqu'à la fin du cadre

	speed=(float)(beginValid + (float)(endValid-beginValid)/2 - initialY)/timeUntil;
	assert(speed!=0);
	cout<<"SPEED :"<<speed;
	timeLine=0;
}

/*

float time_seconds = SDL_GetTicks() / 1000.f;
while(1){
    float new_time = SDL_GetTicks() / 1000.f;
    float delta = new_time - time_seconds;
    time_seconds = new_time;
    updateGamePhysics(delta);
    SDL_RenderClear(renderer);
    renderGamebjects();
    SDL_RenderPresent(renderer); //Will wait here
}


delta représente le temps depuis le dernier appel de la fonction en SECONDES

*/

bool Cadre::update(float delta, const line& currLine) {
	cout<<timeLine<<endl<<delta<<endl;

	if (timeLine==0) timeLine = currLine.time/1000.f;//conversion en secondes
	
	bool ajout=false;

	//On fait avancer les notes existantes
	scrollCadre(delta);

	//Ajout de la ligne, si c'est le moment
	//float actualTime = currLine.time - time; //Actual time représente le temps qu'il reste avant de devoir jouer la ligne
	
	timeLine-=delta;
	assert(timeLine>timeUntil-delta);
	assert(timeUntil-delta>0);


	Note* note;

	if( timeLine < (timeUntil + delta) && timeLine > (timeUntil - delta) ) {
		//On ajoute les notes de la ligne au cadre
		ajout=true;
		timeLine=0; //On réinitialise timeLine
		for(unsigned int i=0;i<5;++i){
			if(currLine.data[i] == '1') { note= new Note(tabPos[i],initialY,i,false,speed);noteTab.push_back(note); }
			else if(currLine.data[i] == '2') { note = new Note(tabPos[i],initialY,i,true,speed);noteTab.push_back(note); }
			
		}

	}
	return ajout;
}


void Cadre::scrollCadre(float delta) {
	Note* tmpNote;
	unsigned int posY;
	for(unsigned int i=0;i<noteTab.size();++i) {
		noteTab[i]->scroll(delta);
		posY = noteTab[i]->getPosY();
		if(posY >= beginValid && posY <=endValid) {
			noteTab[i]->setNeedPlay(); //La note doit être jouée
		}
		else if(posY > endValid) { //La note n'est plus dans le cadre, on l'efface
			tmpNote = noteTab[i];
			noteTab.erase(noteTab.begin() + i);
			delete tmpNote;
		}
	}
}

unsigned int Cadre::getNbNote() const { return noteTab.size();}

Note& Cadre::getNote(unsigned int i) { 
	assert(i<noteTab.size());
	return *noteTab[i];
}

bool Cadre::isEmpty() const { return noteTab.empty();}

int Cadre::getBeginValid() const { return beginValid;}