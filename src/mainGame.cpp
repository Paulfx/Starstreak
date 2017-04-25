#include "game.h"
#include "menu.h"


int main() {

	Menu menu("../data/index");

	Game game(menu.getCurrSong(),menu.getDifficulty(),menu.getMode());

	//Partition& part = game.getPartition();
	//Cadre& game.getCadre() = game.getgame.getCadre()();
	int tps = 0;
	bool ligneAjoutee = false;
	line currLine= game.getPartition().getLine();

	while(true) {


		tps+=16;//ms
		if(ligneAjoutee) {
			currLine=game.getPartition().getLine();
		}
		cout<<"FINI : "<<game.getPartition().isFinished()<<endl;

		if(game.getPartition().isFinished()) break;

		ligneAjoutee=game.getCadre().update(tps,currLine);



		cout<<"------------------------------------"<<endl<<"Nombre de notes : "<<game.getCadre().getNbNote()<<endl;
		for(unsigned int i=0;i<game.getCadre().getNbNote();++i) {
			cout<<"Note numéro : "<<i<<"  Position X : "<<game.getCadre().getNote(i).getPosX()<<endl;
			cout<<"  Position Y : "<<game.getCadre().getNote(i).getPosY()<<endl;
		}

	}
	
	//On finit de dérouler le cadre jusqu'à ce que toutes les notes soient passées
	while(!game.getCadre().isEmpty()) {
		game.getCadre().scrollCadre();

		for(unsigned int i=0;i<game.getCadre().getNbNote();++i) {
			cout<<"Note numéro : "<<i<<"  Position X : "<<game.getCadre().getNote(i).getPosX()<<endl;
			cout<<"  Position Y : "<<game.getCadre().getNote(i).getPosY()<<endl;
		}
	}

	
	return 0;
}