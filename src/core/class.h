#ifndef CLASS_H
#define CLASS_H

#include <string>

using namespace std;

/**
 @struct Stocke toute les informations liées à une chanson à partir de l'index
 */
typedef struct {
	string title,filePartition,fileMusic,fileImage;
	float duration;
} Song;


/**
 @struct Une ligne de jeu = données (eg "10010") + le temps depuis zero
 */
typedef struct {
	string data;
	float time;
    //bool onSequence;
} line;

/**@class note
	@brief Classe gérant les notes
 */
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
    
    /** @brief @brief Constructeur par paramètres
     @param [in] x, y variables de position
     @param [in] c couleur
     @param [in] longBool True si la note est longue (noéte "2")
     @param [in] 
     */
	Note(unsigned int x, unsigned int y, unsigned int c, bool longBool, float speedNote);
    
    /** @brief accesseur de posX
     @return unsigned int
     */
	unsigned int getPosX() const;
    
    /** @brief accesseur de posY
     @return unsigned int
     */
	unsigned int getPosY() const;
    
    /** @brief accesseur de getColor
     @return unsigned int
     */
	unsigned int getColor() const;
    
    /** @brief accesseur de NeedPlay
     @return bool
     */
	bool getNeedPlay() const;
    
    /** @brief accesseur Played
     @return bool
     */
	bool isPlayed() const;
    
    /** @brief accesseur isLong
     @return bool
     */
	bool isLong() const;
    
    /** @brief
     @param delta temps que la note va rester dans le cadre
     */
	void scroll(float delta);
    
    /** @brief mutateur setNeedPlay
     */
	void setNeedPlay();
    
    /** @brief mutateur setPlayed
     */
	void setPlayed();
};

#endif //CLASS_H
