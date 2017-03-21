#include "menu.h"

using namespace std;

Menu::Menu() {
	songTab = NULL;
	currPtr = NULL;
	nbSongs = 0;
}

Menu::Menu(const string& filename) {
	cout<<"Ouverture de : "<<filename<<endl;
	ifstream fichier(filename.c_str());
	assert(fichier.is_open());
	string line;
	unsigned int i=0,j;
	Song* song;

	fichier>>nbSongs; //Récupération du nombre de chansons (donnée membre)


	songTab = new Song* [nbSongs];
	


	while(getline(fichier,line)) {
		
		stringstream lineStream(line); //conversion d'un str en stream
		string word;
		song = new Song;
		j=0;
		while(getline(lineStream,word,',')) {
			switch(j) {
				case 0 : song->title = word; break;
				case 1 : song->filePartition = word; break;
				case 2 : song->fileMusic = word; break;
				case 3 : song->fileImage = word; break;
				case 4 : song->duration = atof(word.c_str()); break;
				default : break;
			}
			j++;
		}

		songTab[i] = song;
		i++;
		song = NULL;
	}

	afficher();


	currPtr = songTab[0];

	
	cout<<"gzehueghuzeghghzeguhguzehguz";
}


Menu::~Menu() {
	cout <<"DESTRU 1111";
	for(unsigned int i=0;i<nbSongs;++i) {
		delete songTab[i];
	}
	delete songTab;
	songTab = NULL;

	cout<<"DESTRUUUU 22222";
}

void Menu::afficher() {
	for(unsigned int i=0;i<nbSongs;++i) {
		cout<<songTab[i]->title<<endl;
	}
}

void Menu::moveUp() {
	currPtr--;
}

void Menu::moveDown() {
	currPtr++;
}