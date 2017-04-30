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
	unsigned int tabPos [5]; //Position des colonnes TODO : a virer
	float timeUntil; // Représente le temps(constant) entre l'arrivée d'une note dans le cadre
				   // et son arrivée dans la zone de validation en secondes
	float speed; //Vitesse des notes par secondes
	unsigned int initialY;
	unsigned int beginValid; //Position en Y du début de la zone de validation
	unsigned int endValid; //Position en Y de la fin de la zone de validation

	float totalTime;
//	Partition* partition;
	//unsigned int movingY;
	vector<Note*> noteTab;

	float timeLine; //Tps de la ligne moins delta en secondes


public :
	/** @brief 
     */
	Cadre();
    
    
    /** @brief
     */
	Cadre(unsigned int pos0,unsigned int pos1,unsigned int pos2,unsigned int pos3,unsigned int pos4, float time, unsigned int initY, unsigned int beginV, unsigned int endV);
	
	~Cadre();
    
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
