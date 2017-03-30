#include "menu.h"

using namespace std;

Menu::Menu() {
	songTab = NULL;
	currI=0;
	nbSongs = 0;
	active = true;
	difficulty = 1;
}

Menu::Menu(const string& filename) : currI(0), active(true), difficulty(1){
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
			song=NULL;
		}
	}
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
	(currI == 0) ? currI=nbSongs-1 : currI=(currI - 1) % nbSongs;
}

void Menu::moveDown() {
	currI = (currI + 1) % nbSongs;
}

void Menu::choose() {
	Game currGame(songTab[currI],difficulty); 
	active = false;
}									

Song** Menu::getSongTab() { return songTab; }

unsigned int Menu::getCurrI() const { return currI; }

unsigned int Menu::getNbSongs() const { return nbSongs; }


unsigned int Menu::getDifficulty() const { return difficulty; }

bool Menu::isActive() const { return active; }


void Menu::increaseDiff(){
	difficulty = (difficulty%3)+1;
}

void Menu::decreaseDiff(){
	difficulty == 1 ? difficulty = 3 : difficulty -= 1;
}

Game& Menu::getGame() {return currGame;}