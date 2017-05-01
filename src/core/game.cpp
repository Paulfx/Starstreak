#include "game.h"

using namespace std;

const int COLUMN_NOTE_0 = 0;
const int COLUMN_NOTE_1 = 150;
const int COLUMN_NOTE_2 = 280;
const int COLUMN_NOTE_3 = 450;
const int COLUMN_NOTE_4 = 600;
const int BEGIN_CADRE = 0;
const int BEGIN_VALIDATION = 500;
const int END_VALIDATION = 600;
const float TIME_UNTIL_DOWN = 1; //dépend de difficulté

Game::Game() {

}


Game::Game(const Song& currSong,unsigned int difficulty,int beginValid) {
	song = currSong;
	partition = new Partition(currSong.filePartition,difficulty);//A CHANGER DIFFICULTY != 1

	cout<<"Partition créée"<<endl;
	cout<<partition->getNbLine()<<endl;

	cadre= new Cadre(COLUMN_NOTE_0,COLUMN_NOTE_1,COLUMN_NOTE_2,COLUMN_NOTE_3,COLUMN_NOTE_4,TIME_UNTIL_DOWN,BEGIN_CADRE,
		beginValid,beginValid+100);
	cout<<"Cadre créé"<<endl;

	score = new Score(partition->getNbLine());
	cout<<"Score créé"<<endl;

	keyboard = new Keyboard();
	cout<<"Keyboard créé"<<endl;

	ligneAjoutee=false;
	currLine=partition->getLine();

}

Game::~Game() {
	delete partition;
	delete cadre;
	delete score;
	delete keyboard;
}

const Song& Game::getSong() { return song;}

Score& Game::getScore() { return *score;}

Cadre& Game::getCadre() { return *cadre;}

Partition& Game::getPartition() { return *partition;}

Keyboard& Game::getKeyboard() { return *keyboard;}

void Game::update(float delta) {

	if(!partition->isFinished()) {

		if(ligneAjoutee) {
			currLine=partition->getLine();
		}
		cadre->scrollCadre(delta,*score);
		ligneAjoutee=cadre->update(delta,currLine);//On regarde si on a ajouté la ligne

	}
	
	else if(!cadre->isEmpty()) {
		//On finit de dérouler le cadre jusqu'à ce que toutes les notes soient passées
		cadre->scrollCadre(delta,*score);
	}
	
	vector<Note*> needPlayTab=cadre->getNeedPlayTab(); //Contient les notes qui doivent être jouée
	score->update(needPlayTab,*keyboard);

}
