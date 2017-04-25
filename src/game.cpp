#include "game.h"

using namespace std;

const int COLUMN_NOTE_0 = 0;
const int COLUMN_NOTE_1 = 150;
const int COLUMN_NOTE_2 = 300;
const int COLUMN_NOTE_3 = 450;
const int COLUMN_NOTE_4 = 600;
const int BEGIN_CADRE = 0;
const int BEGIN_VALIDATION = 500;
const int END_VALIDATION = 550;
const int TIME_UNTIL_DOWN = 3;

Game::Game() {

}


Game::Game(Song& currSong,unsigned int difficulty,bool mode) {
	song = currSong;
	creationMode = mode;
	partition = new Partition(currSong.filePartition,1);//A CHANGER DIFFICULTY != 1

	cout<<"Partition créée"<<endl;
	cout<<partition->getNbLine()<<endl;

	cadre= new Cadre(COLUMN_NOTE_0,COLUMN_NOTE_1,COLUMN_NOTE_2,COLUMN_NOTE_3,COLUMN_NOTE_4,TIME_UNTIL_DOWN,BEGIN_CADRE,
		BEGIN_VALIDATION,END_VALIDATION);
	cout<<"Cadre créé"<<endl;

	score = new Score(partition->getNbLine());
	cout<<"Score créé"<<endl;


	ligneAjoutee=false;
	currLine=partition->getLine();



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

void Game::update(float delta) {

	if(!partition->isFinished()) {

		if(ligneAjoutee) {
			currLine=partition->getLine();
		}
		cout<<"FINI : "<<partition->isFinished()<<endl;

		ligneAjoutee=cadre->update(delta,currLine);


		for(unsigned int i=0;i<cadre->getNbNote();++i) {
			cout<<"Note numéro : "<<i<<"  Position X : "<<cadre->getNote(i).getPosX()<<endl;
			cout<<"  Position Y : "<<cadre->getNote(i).getPosY()<<endl;
		}


	}
	
	else if(!cadre->isEmpty()) cadre->scrollCadre(delta);
	//On finit de dérouler le cadre jusqu'à ce que toutes les notes soient passées


}