#ifndef _CADRE_H
#define _CADRE_H

#include "partition.h"

class Note {

private :
	int posX,posY;
	int couleur;

public :
	Note();

	Note(int posX, int posY, int couleur);
};

/**@class Cadre
	@brief  S'occupe du cadre déroulant des notes.
*/
class Cadre {

private :
	int tabPos [5]; //Position des colonnes
	int cspeed; // Ou plutot temps de défilement, représente le temps(constant) entre l'arrivée d'une note dans le cadre
				// et son arrivée dans la zone de validation
	Partition* partition;
	vector<Note> noteTab;

public :
	
	Cadre();

	Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, int speed, const Partition& currPart);
	

	/**@brief met à jour le cadre.
	@param time représente le temps écoulé (en ms) depuis le lancement du son
	*/
	void update(uint32_t time); //Lit partition et remplit noteTab des notes correspondantes, et fait défiler celles existantes



};










#endif