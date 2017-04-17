#ifndef _CADRE_H
#define _CADRE_H

#include "partition.h"

class Note {
	int posX,posY;
	int couleur;
};


class Cadre {

private :
	int cpos0,cpos1,cpos2,cpos3,cpos4; //Position des colonnes
	int cspeed;
	Partition* partition;
	vector<Note> noteTab;

public :
	
	Cadre();

	Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, int speed, const Partition& currPart);
	
	void update(uint32_t time); //Lit partition et remplit noteTab des notes correspondantes, et fait défiler celles existantes



};










#endif