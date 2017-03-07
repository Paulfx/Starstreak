#ifndef PARTITION_H
#define PARTITION_H


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>


using namespace std;


typedef struct { //Une ligne de jeu = données (eg "1001") + temps jusqu'à la prochaine ligne
	string data; 
	float time;
}line;



class Partition {

	private :

		line* partition; //tableau 2D 
		int nbLine;
		int duree;

	public :
		/**
		*/
		Partition();

		/**@brief Constructeur
		*/
		Partition(const string & filename,int difficulty);

		/**@brief Destructeur
		*/
		~Partition();

		void afficher();


};

#endif
