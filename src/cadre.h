#ifndef _CADRE_H
#define _CADRE_H

#include "partition.h"
#include <vector>
#include <string>

class Note {

private :
	int posX;
	int posY;
	int color; //0=vert , 1=rouge, 2=jaune, 3=bleu, 4=marron
	bool longDuration; //True si la note est longue (noéte "2")

public :
	Note();
	Note(int x, int y, int c, bool longBool);
	int getPosX() const;
	int getPosY() const;
	int getColor() const;
	void scroll(int movement);

};

/**@class Cadre
	@brief  S'occupe du cadre déroulant des notes.
*/
class Cadre {

private :
	int tabPos [5]; //Position des colonnes
	int cspeed; // Ou plutot temps de défilement, représente le temps(constant) entre l'arrivée d'une note dans le cadre
				// et son arrivée dans la zone de validation
	int initialY;
	int beginningValid; //Position en Y du début de la zone de validation
	int endValid; //Position en Y de la fin de la zone de validation
//	Partition* partition;
	int movingY;
	vector<Note*> noteTab;

public :
	
	Cadre();

	Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, int speed, int initY, int beginV, int endV);
	

	/**@brief met à jour le cadre.
	@param time représente le temps écoulé (en ms) depuis le lancement du son
	@return true si currLine est ajoutée au cadre, false sinon
	*/
	bool update(uint32_t time, line* currLine); //Lit partition et remplit noteTab des notes correspondantes, et fait défiler celles existantes

	void scrollCadre();

	int getNbNote() const;

	Note* getPtrNote(int i);

	bool isEmpty() const;

};










#endif