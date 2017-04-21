#include "cadre.h"
#include "partition.h"
#include <iostream>

using namespace std;


int main() {

	Cadre cadre(0,1,2,3,4,500,0,100,150);

	Partition part("../data/songs/sth",1);
	int tps = 0;
	bool ligneAjoutee = false;
	line* currLine= part.getLine();
	
	while(true) {
		tps+=16;//ms
		if(ligneAjoutee) {
			currLine=part.getLine();
		}
		cout<<"FINI : "<<part.isFinished()<<endl;

		if(part.isFinished()) break;

		ligneAjoutee=cadre.update(tps,currLine);



		cout<<"------------------------------------"<<endl<<"Nombre de notes : "<<cadre.getNbNote()<<endl;
		for(unsigned int i=0;i<cadre.getNbNote();++i) {
			cout<<"Note numéro : "<<i<<"  Position X : "<<cadre.getPtrNote(i)->getPosX()<<endl;
			cout<<"  Position Y : "<<cadre.getPtrNote(i)->getPosY()<<endl;
		}

	}

	//On finit de dérouler le cadre jusqu'à ce que toutes les notes soient passées
	while(!cadre.isEmpty()) {
		cadre.scrollCadre();

		for(unsigned int i=0;i<cadre.getNbNote();++i) {
			cout<<"Note numéro : "<<i<<"  Position X : "<<cadre.getPtrNote(i)->getPosX()<<endl;
			cout<<"  Position Y : "<<cadre.getPtrNote(i)->getPosY()<<endl;
		}
	}
	
	return 0;
}