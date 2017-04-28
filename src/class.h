#ifndef CLASS_H
#define CLASS_H

#include <string>

using namespace std;

typedef struct {
	string title,filePartition,fileMusic,fileImage;
	float duration;
} Song;

typedef struct { //Une ligne de jeu = données (eg "1001") + temps jusqu'à la prochaine ligne
	string data; 
	float time;
    //bool onSequence;
} line;


class Note {

private :
	int posX;
	int posY;
	int color; //0=vert , 1=rouge, 2=jaune, 3=bleu, 4=orange
	bool longDuration; //True si la note est longue (noéte "2")
	float speed;
	bool played = false; //true si le joueur joue la note
	bool needPlay = false; //true si le joueur doit jouer la note
public :
	Note();
	Note(int x, int y, int c, bool longBool, float speedNote);
	int getPosX() const;
	int getPosY() const;
	int getColor() const;
	bool getNeedPlay() const;
	bool isPlayed() const;
	bool isLong() const;
	void scroll(float delta);
	void setNeedPlay();
	void setPlayed();
};

#endif //CLASS_H