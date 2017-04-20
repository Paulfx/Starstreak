#include "game.h"

using namespace std;

const int COLUMN_NOTE_0 = 0;
const int COLUMN_NOTE_1 = 50;
const int COLUMN_NOTE_2 = 100;
const int COLUMN_NOTE_3 = 150;
const int COLUMN_NOTE_4 = 200;
const int BEGIN_CADRE = 0;
const int BEGIN_VALIDATION = 200;
const int END_VALIDATION = 250;
const int SPEED_NOTE = 500;

Game::Game() {

}


Game::Game(Song& currSong,unsigned int difficulty,bool mode) {
	song = currSong;
	creationMode = mode;
	partition = new Partition(currSong.filePartition,difficulty);

	cout<<"Partition créée"<<endl;
	cout<<partition->getNbLine()<<endl;

	cadre= new Cadre(COLUMN_NOTE_0,COLUMN_NOTE_1,COLUMN_NOTE_2,COLUMN_NOTE_3,COLUMN_NOTE_4,SPEED_NOTE,BEGIN_CADRE,
		BEGIN_VALIDATION,END_VALIDATION);
	cout<<"Cadre créé"<<endl;

	score = new Score(partition->getNbLine());
	cout<<"Score créé"<<endl;
}

Game::~Game() {
	delete partition;
	delete cadre;
	delete score;
}

Song& Game::getSong() { return song;}

Score& Game::getScore() { return *score;}

Cadre& Game::getCadre() { return *cadre;}

Partition& Game::getPartition() { return *partition;}
