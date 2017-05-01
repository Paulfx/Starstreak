#ifndef MENU_H
#define MENU_H


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include "game.h"
#include "class.h"

using namespace std;

class Menu {

private :
	
	Song** songTab; //tableau de liens sur song
	unsigned int currI; //indice dans songTab de currPtr
	unsigned int nbSongs; //taille du tab
	bool active; //false si menu inactif = une game est active
	//Game* currGame; //La partie en cours
	unsigned int difficulty;// 1, 2 ou 3
	bool mode;
    

	
public :
	/**@brief Constructeur par défaut 
	*/
	Menu();

	/**@brief Constructeur
	
	Constructeur de la classe Menu

	Ouvre le fichier 'filename' et remplit songTab des Song correspondants

	   @param[in,out] filename
	*/
	Menu(const string& filename);

	/**@brief Destructeur
	   Destructeur de la classe Menu
	   Libère l'espace alloué dans le tableau songTab
	*/
	~Menu();

	/**@brief Modifie le currPtr de manière à remonter dans le menu
	*/
	void moveUp();

	/**@brief Modifie le currPtr de manière à descendre dans le menu
	*/
	void moveDown();

	/**@brief Crée la partie associée à la chanson pointée par currPtr
		Rend le menu inactif
	*/
	Song& getCurrSong();
    
    /** @brief
     */
	const Song& getConstCurrSong(); 

    /** @brief
     */
	unsigned int getCurrI() const;

    /** @brief
     */
	unsigned int getNbSongs() const;

    /** @brief
     */
    unsigned int getDifficulty() const;
    
    /** @brief
     */
	Game& getGame();

    /** @brief
     */
	bool isActive() const;

    /** @brief
     */
	void increaseDiff();

    /** @brief
     */
	void decreaseDiff();

    /** @brief
     */
	bool getMode() const;

	/** @brief Renvoie le tab des noms de chansons
     */
    string getList();

    /** @brief
     */
    string getTitleSong(unsigned int i);

};

#endif
