#include "game.h"

using namespace std;

Game::Game() {

}


Game::Game(Song* currSong,unsigned int difficulty) {
	Partition partition(currSong->filePartition,difficulty);

	cout<<"Partition créée"<<endl;

	for (unsigned int i=0 && !partition.isFinished();i<10;++i) {
		cadre.push_back(partition.getLine().data);

	}

	cout<<"Cadre créé"<<endl;

	Score score(partition.getNbLine());   
}

Game::~Game() {

}

const vector<string> Game::getCadre() const { return cadre;}

Song Game::getSong() const { return song;}

Score Game::getScore() const { return score;}

void Game::defileCadre(uint32_t time) {} // A FAIRE ! DEFILE LE VECTOR
