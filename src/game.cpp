#include "game.h"

using namespace std;

Game::Game() {

}


Game::Game(Song* currSong,unsigned int difficulty) {
	Partition partition(currSong->filePartition,difficulty);

	for (unsigned int i = 0;i<10;) {
		cadre.push_back(partition.getLine());	
	}

	Score score(partition.getNbLine());   
}

Game::~Game() {

}

queue<line> Game::getCadre() const { return cadre;}

Song Game::getSong() const { return song;}

Score Game::getScore() const { return score;}

void Game::defileCadre() {} // A FAIRE ! DEFILE LE VECTOR