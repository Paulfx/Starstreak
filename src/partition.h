#ifndef PARTITION_H
#define PARTITION_H


#include <stdlib.h>

using namespace std;

class Partition {

	private :

		char** partition; //tableau 2D

	public :
		/**
		*/
		Partition() {

		} 

		/**@brief Constructeur
		*/
		Partition(const string & filename,int difficulty);

		/**@brief Destructeur
		*/
		~Partition();


};

#endif

