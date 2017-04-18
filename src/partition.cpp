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
	cout<<"Ouverture de : "<<filename<<endl;
	ifstream fichier(filename.c_str());
	assert(fichier.is_open());

	index = 0;
	end=false;

	string difficultyLine,strNbBeginning;
	getline(fichier,difficultyLine);
	stringstream ss(difficultyLine); //Conversion de str en flux
	for (unsigned int i=0;i<difficulty;i++) {
		getline(ss,strNbBeginning,','); //Séparation de la ligne selon la virgule
	}
	int nbBeginning = std::stoi(strNbBeginning.c_str()); //nbr de caractère avant le début de la partition

	fichier.seekg(nbBeginning,ios::beg); // On se déplace au début de la partition

	fichier >> nbLine;
	fichier >> duree;
	partition = new line[nbLine];

	for(unsigned int i=0;i<nbLine;i++) {
		fichier >> partition[i].data >> partition[i].time;// >> partition[i].onSequence;
	}

	fichier.close();

	cout<<"Fichier bien ouvert"<<endl;

}

Partition::~Partition() {
	if(partition != NULL) {
		delete [] partition;
		partition = NULL;
	}
}

void Partition::afficher() {
	for (unsigned int i = 0 ; i<nbLine; i++) {
		cout<<partition[i].data<<endl;
	}
}

int Partition::getNbLine() {return nbLine;}
/*
line Partition::getLine() {
	line l;
	if(index<nbLine) {
		l = partition[index];
		index+=1;
	}

	else if(index == nbLine) {
		end = true;
	}
	return l;
}
*/

bool Partition::getLine(line& currLine) {
	assert(index<=nbLine);
	if(index==nbLine) return false;
	
	index++;
	currLine=partition[index];
	cout<<currLine.data;
	return true;
}

bool Partition::isFinished() {return end;}