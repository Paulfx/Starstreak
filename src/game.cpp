#include "game.h"

using namespace std;

Game::Game() {

}


Game::Game(Song* song,int difficulty) {
	Partition partition(song->filePartition,difficulty);

	partition.afficher();
	//Score score(partition.getNbLine());

}

Game::~Game() {

}