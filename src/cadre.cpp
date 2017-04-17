
#include "cadre.h"



Cadre::Cadre() {}

Cadre::Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, int speed, const Partition& currPart){
	cpos0 = pos0;
	cpos1 = pos1;
	cpos2 = pos2;
	cpos3 = pos3;
	cpos4 = pos4;
	cspeed = speed;
	partition = currPart;
}

void Cadre::update(uint32_t time) {}