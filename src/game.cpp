#include "game.h"

using namespace std;

Game::Game() {

}


Game::Game(Song* currSong,int difficulty) {
	Partition partition(currSong->filePartition,difficulty);



	//song = *currSong; 
	partition.afficher();
	//Score score(partition.getNbLine());

}

Game::~Game() {

}