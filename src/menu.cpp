#include "menu.h"

using namespace std;


Menu::Menu() {

}

Menu::Menu(const string& filename) {
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