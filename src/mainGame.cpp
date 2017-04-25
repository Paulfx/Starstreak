#include "game.h"
#include "menu.h"
#include <ctime>


int main() {

	Menu menu("../data/index");

	Game game(menu.getCurrSong(),menu.getDifficulty(),menu.getMode());


	//Partition& part = game.getPartition();
	//Cadre& game.getCadre() = game.getgame.getCadre()();
	unsigned int tps = 0;
	bool ligneAjoutee = false;
	line currLine= game.getPartition().getLine();

/*
	float time_seconds = SDL_GetTicks() / 1000.f;
while(1){
    float new_time = SDL_GetTicks() / 1000.f;
    float delta = new_time - time_seconds;
    time_seconds = new_time
*/

	clock_t time_seconds = clock();
	while(true) {
		clock_t new_time = clock();
		float delta = float(new_time) - float(time_seconds);
		time_seconds=new_time;

		cout<<"DELTA :"<<delta<<endl;

		if(ligneAjoutee) {
			currLine=game.getPartition().getLine();
		}
		cout<<"FINI : "<<game.getPartition().isFinished()<<endl;

		if(game.getPartition().isFinished()) break;

		ligneAjoutee=game.getCadre().update(delta,currLine);



		cout<<"------------------------------------"<<endl<<"Nombre de notes : "<<game.getCadre().getNbNote()<<endl;
		for(unsigned int i=0;i<game.getCadre().getNbNote();++i) {
			cout<<"Note numéro : "<<i<<"  Position X : "<<game.getCadre().getNote(i).getPosX()<<endl;
			cout<<"  Position Y : "<<game.getCadre().getNote(i).getPosY()<<endl;
		}

	}
	
	//On finit de dérouler le cadre jusqu'à ce que toutes les notes soient passées
	while(!game.getCadre().isEmpty()) {
		clock_t new_time = clock();
		float delta = float(new_time) - float(time_seconds);
		time_seconds=new_time;

		cout<<"DELTA :"<<delta<<endl;
		

		game.getCadre().scrollCadre(delta);

		for(unsigned int i=0;i<game.getCadre().getNbNote();++i) {
			cout<<"Note numéro : "<<i<<"  Position X : "<<game.getCadre().getNote(i).getPosX()<<endl;
			cout<<"  Position Y : "<<game.getCadre().getNote(i).getPosY()<<endl;
		}
	}

	
	return 0;
}