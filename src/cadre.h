#ifndef _CADRE_H
#define _CADRE_H

#include "class.h"
#include "partition.h"
#include "score.h"
#include <vector>
#include <string>


/**@class Cadre
	@brief  S'occupe du cadre déroulant des notes.
*/
class Cadre {

private :
	int tabPos [5]; //Position des colonnes
	float timeUntil; // Représente le temps(constant) entre l'arrivée d'une note dans le cadre
				   // et son arrivée dans la zone de validation en secondes
	float speed; //Vitesse des notes par secondes
	int initialY;
	int beginValid; //Position en Y du début de la zone de validation
	int endValid; //Position en Y de la fin de la zone de validation
//	Partition* partition;
	//int movingY;
	vector<Note*> noteTab;

	float timeLine; //Tps de la ligne moins delta en secondes


public :
	/** @brief 
     */
	Cadre();
    
    
    /** @brief
     */
	Cadre(int pos0,int pos1,int pos2,int pos3,int pos4, float time, int initY, int beginV, int endV);
	
    
	/**@brief met à jour le cadre.
	@param time représente le temps écoulé (en ms) depuis le lancement du son
	@return true si currLine est ajoutée au cadre, false sinon
	*/
	bool update(float delta, const line& currLine); //Lit partition et remplit noteTab des notes correspondantes, et fait défiler celles existantes

    
    /** @brief
     */
	void scrollCadre(float delta, Score& score);
    
    
    /** @brief
     */
	unsigned int getNbNote() const;

    /** @brief
     */
	Note& getNote(unsigned int i);

	/** @brief
     */
    Note* getPtrNote(unsigned int i);

    /** @brief
     */
	bool isEmpty() const;

    
    /** @brief
     */
	int getBeginValid() const;

	int getTabPos(unsigned int i) const;

};


#endif
