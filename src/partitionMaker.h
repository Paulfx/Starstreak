#ifndef PARTITION_MAKER_H
#define PARTITION_MAKER_H

#include "class.h"
#include "keyboard.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

/**@class PartitionMaker
@brief Remplace la classe game si le mode création est activé (pour les développeurs)
Permet de créer un fichier complet de partition (toutes les difficultés sont crées en même temps)
*/
class PartitionMaker {

	private :
	
		Keyboard* keyboard;
		Song song;
		int difficulty; //compteur de la difficulté
		bool end;
		
		string data1;
		unsigned int numberLine1;
		string data2; //Contient les lignes (eg. "10011 6542\n")
		unsigned int numberLine2;
		string data3; 
		unsigned int numberLine3;
	public :
		
		/**@brief Constructeur
         @param 
		*/
		PartitionMaker(const Song& currSong);

		/**@brief Destructeur
		*/
		~PartitionMaker();

		void update(unsigned int msTime, const string& line);

		/**@brief Calcule les bonnes valeurs de décalage de buffer pour les difficultés
		Modifie les paramètres en entrée.
		Si la somme des nbChar avec count ajoute une unité à nbChar, alors on resomme le nombre d'unités ajoutées aux trois nbChar
		@param [in,out]
		@param [in,out]
		@param [in,out]
		@param [in] count nombre de caractères (ou digits) des 3 nbChar, plus 2 (virgules de la première ligne)
		*/
		void calcNbChar(unsigned int& nbChar1,unsigned int& nbChar2,unsigned int& nbChar3, unsigned int count);

		/**@brief Calcule et renvoie le nombre d'unités de number
		*/
		int nbDigits(unsigned int number);

		Keyboard& getKeyboard();

		const Song& getSong();

		unsigned int getDifficulty();

		bool isEnded() const;
		
		void increaseDifficulty();

		void save();

};

#endif //PARTITION_MAKER