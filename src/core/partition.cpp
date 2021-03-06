#include "partition.h"
#include <sstream>
#include <iostream>
#include <string>

Partition::Partition() {
	partition = NULL;
	index=0;
	end = false;
}

Partition::Partition(const string & filename,unsigned int difficulty) {
	string filenameDiff=filename+to_string(difficulty);
	cout<<"Ouverture de : "<<filenameDiff<<endl;
	ifstream fichier(filenameDiff.c_str());
	assert(fichier.is_open());
	index = 0;
	end=false;

	fichier >> nbLine;
	partition = new line[nbLine];

	for(unsigned int i=0;i<nbLine;i++) {
		fichier >> partition[i].data >> partition[i].time;// >> partition[i].onSequence;
	}

	fichier.close();
}

Partition::~Partition() {
	if(partition != NULL) {
		delete [] partition;
		partition = NULL;
	}
}	

int Partition::getNbLine() {return nbLine;}

line& Partition::getLine() {
	assert(index<nbLine);
	line& tmp = partition[index];
	index++;
	return tmp;
}

bool Partition::isFinished() {
	if(index==nbLine) return true;
	return false;
}
