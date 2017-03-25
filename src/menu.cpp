#include "menu.h"

using namespace std;

Menu::Menu() {
	songTab = NULL;
	currPtr = NULL;
	nbSongs = 0;
	isActive = true;
	currGame = NULL;
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
			songTab[j] = song;
			j++;
			song = NULL;
		}
	}
	currPtr = songTab[0];
	isActive = true;
	currGame = NULL;
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
	currPtr--; //Liste chainée pour tourner en boucle ?
}

void Menu::moveDown() {
	currPtr++;
}

void Menu::choose() {
	Game currGame(currPtr,0); // Difficulté, pourquoi pas dans game que cela se choisit, 
	isActive = false;
}									//on lance la partie et on choisit juste avant de jouer, plus facile car dans game on accède a la difficulté
									//qu'on envoie à Partition