#include "game.h"

using namespace std;

Game::Game() {

}


Game::Game(Song* currSong,unsigned int difficulty) {
	Partition partition(currSong->filePartition,difficulty);

    partition.afficher();
	/*for (unsigned int i = 0;i<10;) {
		cadre.push(partition.getLine());	
	}*/
	
	Score score(partition.getNbLine());
    fail=true;
    

}

Game::~Game() {

}

bool Game::isFail() {
    return fail;
}
