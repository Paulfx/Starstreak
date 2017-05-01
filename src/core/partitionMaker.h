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
		
		string data;
		unsigned int numberLine;
		/*
		string data2; //Contient les lignes (eg. "10011 6542\n")
		unsigned int numberLine2;
		string data3; 
		unsigned int numberLine3;*/
	public :
		
		/**@brief Constructeur
         @param 
		*/
		PartitionMaker(const Song& currSong,unsigned int currDifficulty);

		/**@brief Destructeur
		*/
		~PartitionMaker();

		void update(unsigned int msTime, const string& line);

		Keyboard& getKeyboard();

		const Song& getSong();

		unsigned int getDifficulty();

		void save();

};

#endif //PARTITION_MAKER