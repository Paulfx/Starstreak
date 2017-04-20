#include "menu.h"

Menu::Menu() {
	songTab = NULL;
	currI=0;
	nbSongs = 0;
	active = true;
	difficulty = 1;
	
	
	cout << endl << "COUCOU de l'init menu sans filename" << endl << endl ;
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

	cout << "Coucou de l'init menu avec filename : " << nbSongs << endl;
	cout << "Adresse : "<< &nbSongs << endl << endl;
    
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


//Fonction D'affichage pour la SDL
//Recuperation des noms de chansons disponibles un a un dans un vector -> pointeur ?
//
/*
string Menu::getList(){

    cout << "Adresse : "<< &nbSongs << endl;
    cout << "coucou from getList :" << nbSongs << endl;
    //ListSong.reserve(nbSongs); //pas sur qu'il y en ait besoin avec push_back
    
    
    
    string ListSong[nbSongs];
    int i=0;
    while(songTab[i]!=NULL){
        ListSong[i]=(songTab[i]->title);
    	i++;
    }
    
return ListSong;
}*/

string Menu::getTitleSong(int i){
    return songTab[i]->title;
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
	currGame = new Game(songTab[currI],difficulty); 
	active = false;
}									

Song** Menu::getSongTab() { return songTab; }

unsigned int Menu::getCurrI() const { return currI; }

unsigned int Menu::getNbSongs() const { 
cout << "Adresse : "<< &nbSongs << endl;
cout << "coucou de get nbSongs : " << nbSongs << endl;
return nbSongs; }


unsigned int Menu::getDifficulty() const { return difficulty; }

bool Menu::isActive() const { return active; }


void Menu::increaseDiff(){
	difficulty = (difficulty%3)+1;
}

void Menu::decreaseDiff(){
	difficulty == 1 ? difficulty = 3 : difficulty -= 1;
}

Game* Menu::getGame() {return currGame;}
