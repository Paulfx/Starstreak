#include "partition.h"

Partition::Partition() {
	partition = NULL;
}

Partition::Partition(const string & filename,int difficulty) {
	cout<<"Ouverture de : "<<filename<<endl;
	ifstream fichier(filename.c_str());
	assert(fichier.is_open());
	fichier >> nbLine;

	partition = new Line

	for(int i=0;i<nbLine;i++) {

	}


	fichier.close();

}

Partition::~Partition() {
	cout<<"DANS LE DESTRUUUU"<<endl;
	if(partition != NULL) {
		delete [] partition;
		partition = NULL;
	}
}