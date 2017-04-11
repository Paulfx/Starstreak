#ifndef MENU_H
#define MENU_H


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include "game.h"
#include "struct.h"

using namespace std;

class Menu {

private :
	
	Song** songTab; //tableau de liens sur song
	unsigned int currI; //indice dans songTab de currPtr
	unsigned int nbSongs; //taille du tab
	bool active; //false si menu inactif = une game est active
	Game* currGame; //La partie en cours
	unsigned int difficulty; 


	
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

	void afficher();

	/**@brief Modifie le currPtr de manière à remonter dans le menu
	*/
	void moveUp();

	/**@brief Modifie le currPtr de manière à descendre dans le menu
	*/
	void moveDown();

	/**@brief Crée la partie associée à la chanson pointée par currPtr
		Rend le menu inactif
	*/
	void choose();

	Song** getSongTab();

	unsigned int getCurrI() const;

	unsigned int getNbSongs() const;

	unsigned int getDifficulty() const;

	Game* getGame();

	bool isActive() const;

	void increaseDiff();

	void decreaseDiff();


};

#endif
