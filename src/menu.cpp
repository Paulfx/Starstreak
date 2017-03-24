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
	unsigned int i,j=0;
	Song* song;

	string word;


	fichier>>nbSongs;
	songTab = new Song*[nbSongs];

	while(getline(fichier,line)) {
		
		if(!line.empty()) {
			stringstream lineStream(line);
			i=0;
			song = new Song;

			

			while(getline(lineStream,word,',')) {

				switch(i) {
					case 0 : song->title = word; break;
					case 1 : song->filePartition = word; break;
					case 2 : song->fileMusic = word; break;
					case 3 : song->fileImage = word; break;
					case 4 : song->duration = atof(word.c_str()); break;
					default : break;
				}

				i++;
			}

			//cout<<song->title<<song->fileImage<<endl;
			
			songTab[j] = song;
			j++;
			song = NULL;

		}
	}





/*
	fichier>>nbSongs; //Récupération du nombre de chansons (donnée membre)



	songTab = new Song* [nbSongs];
	


	while(getline(fichier,line)) {
		
		stringstream lineStream(line); //conversion d'un str en stream
		string word;
		song = new Song;
		j=0;
		while(getline(lineStream,word,',')) {
			cout<<word;
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


	currPtr = songTab[0];*/

}


Menu::~Menu() {


	for(unsigned int i =0;i<nbSongs;i++) {
		delete songTab[i];
	}
	
	delete songTab;
	songTab = NULL;
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