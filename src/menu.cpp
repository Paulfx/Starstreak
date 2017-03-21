#include "menu.h"

using namespace std;

Menu::Menu() {

}

Menu::Menu(const string& filename) {
	cout<<"Ouverture de : "<<filename<<endl;
	ifstream fichier(filename.c_str());
	assert(fichier.is_open());
	
	string line;
	int nbSongs;

	fichier>>nbSongs;


	songTab = new Song* [nbSongs];

	while(getline(fichier,line)) {

		stringstream lineStream(line); //conversion d'un str en stream
		string word;
		Song song = new Song;
		int i=0;

		while(getline(lineStream,word,',')) {
			switch(i) {
				case 0 : song.title = word; break;
				case 1 : song.filePartition = word; break;
				case 2 : song.fileMusic = word; break;
				case 3 : song.fileImage = word; break;
				case 4 : song.duration = word; break;
				default : break;
			}

			i++;
			
		}

	}

	fichier.close();
}

void Menu::afficher() {

}