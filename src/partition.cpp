#include "partition.h"

Partition::Partition() {
	partition = NULL;
}

Partition::Partition(const string & filename,int difficulty) {
	cout<<"Ouverture de : "<<filename<<endl;
	ifstream fichier(filename.c_str());
	assert(fichier.is_open());
	fichier >> nbLine;
	fichier >> duree;

	partition = new line[nbLine];

	for(unsigned int i=0;i<nbLine;i++) {
		fichier >> partition[i].data >> partition[i].time;
	}

	fichier.close();

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

