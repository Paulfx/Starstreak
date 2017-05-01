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
	string filename=song.filePartition+to_string(difficulty);
	ofstream fichier(filename.c_str());
	fichier<<numberLine<<"\n";
	fichier<<data;
	fichier.close();
}

Keyboard& PartitionMaker::getKeyboard() { return *keyboard;}

const Song& PartitionMaker::getSong() { return song;}

unsigned int PartitionMaker::getDifficulty() { return difficulty;}

