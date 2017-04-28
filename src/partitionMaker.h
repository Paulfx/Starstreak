#ifndef PARTITION_MAKER_H
#define PARTITION_MAKER_H

#include "class.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

class PartitionMaker {

	private :

		vector<string> data; //Contient les lignes (eg. "10011 6542")

	public :
		/**
		*/
		PartitionMaker();

		/**@brief Constructeur
         @param filename : nom du fichier contenant la partition
         @param difficulty : 1 pour facile, 2 moyen et 3 difficile
		*/
		PartitionMaker(const string & filename,unsigned int difficulty);

		/**@brief Destructeur
		*/
		~PartitionMaker();

};

#endif //PARTITION_MAKER