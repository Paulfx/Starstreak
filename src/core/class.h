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
	unsigned int posX; //Colonne
	unsigned int posY;
	unsigned int color; //0=vert , 1=rouge, 2=jaune, 3=bleu, 4=orange
	bool longDuration; //True si la note est longue (noéte "2")
	float speed;
	bool played = false; //true si le joueur joue la note
	bool needPlay = false; //true si le joueur doit jouer la note
public :
	Note();
    
    /** @brief
     */
	Note(unsigned int x, unsigned int y, unsigned int c, bool longBool, float speedNote);
    
    /** @brief
     */
	unsigned int getPosX() const;
    
    /** @brief
     */
	unsigned int getPosY() const;
    
    /** @brief
     */
	unsigned int getColor() const;
    
    /** @brief
     */
	bool getNeedPlay() const;
    
    /** @brief
     */
	bool isPlayed() const;
    
    /** @brief
     */
	bool isLong() const;
    
    /** @brief
     */
	void scroll(float delta);
    
    /** @brief
     */
	void setNeedPlay();
    
    /** @brief
     */
	void setPlayed();
};

#endif //CLASS_H
