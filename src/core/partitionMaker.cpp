#include "partitionMaker.h"


PartitionMaker::PartitionMaker(const Song& currSong,unsigned int currDifficulty){
	difficulty=currDifficulty;
	numberLine=0;
	song=currSong;
	keyboard = new Keyboard();
}



PartitionMaker::~PartitionMaker(){
	delete keyboard;
}


void PartitionMaker::update(unsigned int msTime, const string& line) {
	if(line!="00000") {
		string fullLine = line +" "+to_string(msTime)+"\n";
		data+=fullLine;
		numberLine++;
	}
}

void PartitionMaker::save() {
	/*
	string dataDiff1 = numberLine1+"\n"+data1+"\n";
	string dataDiff2 = numberLine2+"\n"+data2+"\n";
	string dataDiff3 = numberLine3+"\n"+data3+"\n";

	int numberChar1 = dataDiff1.length();
	int numberChar2 = dataDiff2.length();

	//Nombre de caractère pour aller à la difficulté i, sans compter la première ligne
	unsigned int nbCharToDifficulty1 = 1;
	unsigned int nbCharToDifficulty2 = numberChar1;
	unsigned int nbCharToDifficulty3 = numberChar1 + numberChar2;
	//Nombre de caractère de la première ligne
	unsigned int nbCharFirstLine = 1+nbDigits(nbCharToDifficulty2)+nbDigits(nbCharToDifficulty3)+2; //2 correspond aux virgules de la première ligne

	calcNbChar(nbCharToDifficulty1,nbCharToDifficulty2,nbCharToDifficulty3,nbCharFirstLine);
	


	string fullData = to_string(nbCharToDifficulty1)+","+to_string(nbCharToDifficulty2)+","+to_string(nbCharToDifficulty3)+"\n"+data1+data2+data3;
	cout<<fullData<<endl;

	*/
	/* Sauvegarde */
	string filename=song.filePartition+to_string(difficulty);
	ofstream fichier(filename.c_str());
	fichier<<numberLine<<"\n";
	fichier<<data;
	fichier.close();

}
/*
void PartitionMaker::calcNbChar(unsigned int& nbChar1,unsigned int& nbChar2,unsigned int& nbChar3, unsigned int count) {
	unsigned int tmpCount;
	bool finished=false;
	while(!finished) {
		nbChar1+=count;
		nbChar2+=count;
		nbChar3+=count;

		tmpCount = (nbDigits(nbChar1)+nbDigits(nbChar2)+nbDigits(nbChar3)+2) - count;
		if(tmpCount==0) {
			//Aucune unité n'a été rajoutée
			finished=true;
		}
		else count = tmpCount;
	}
}

int PartitionMaker::nbDigits(unsigned int number) {
	int digits=0;
	while(number) {
		number /= 10;
		digits++;
	}
	return digits;
}
*/
Keyboard& PartitionMaker::getKeyboard() { return *keyboard;}

const Song& PartitionMaker::getSong() { return song;}

unsigned int PartitionMaker::getDifficulty() { return difficulty;}

