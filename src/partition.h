#ifndef PARTITION_H
#define PARTITION_H

#include "struct.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>


using namespace std;

class Partition {

	private :

		line* partition; //tableau 1D
		unsigned int nbLine;
		unsigned int duree;
		unsigned int index; //Indice tenant compte de l'avancée dans partition
		bool end;

	public :
		/**
		*/
		Partition();

		/**@brief Constructeur
         @param filename : nom du fichier contenant la partition
         @param difficulty : 1 pour facile, 2 moyen et 3 difficile
		*/
		Partition(const string & filename,unsigned int difficulty);

		/**@brief Destructeur
		*/
		~Partition();

		int getNbLine();

		/**@brief Renvoie une référence vers la prochaine ligne de partition
			Incrémente index
		*/
		line& getLine();

		bool isFinished();
};

#endif
