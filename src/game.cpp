#include "game.h"

using namespace std;

Game::Game() {

}


Game::Game(Song* currSong,unsigned int difficulty) {
	song = currSong;

	Partition partition(currSong->filePartition,difficulty);

	cout<<"Partition créée"<<endl;




	//Cadre cadre(0,1,2,3,4,10);


/*
	for (unsigned int i=0 && !partition.isFinished();i<10;++i) {
		cadre.push_back(partition.getLine().data);
	}

	cout<<"Cadre créé"<<endl;*/

	Score score(partition.getNbLine());   
}

Game::~Game() {

}

const vector<string> Game::getCadre() const { return cadre;}

Song Game::getSong() const { return song;}

Score Game::getScore() const { return score;}

void Game::defileCadre(uint32_t time) {} // A FAIRE ! DEFILE LE VECTOR
