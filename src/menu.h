#ifndef MENU_H
#define MENU_H


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

typedef struct {
	string title,filePartition,fileMusic,fileImage;
	float duration;
} Song;


class Menu {

private :
	
	Song** songTab; //tableau de liens sur song
	Song* currPtr; //ptr sur la chanson ciblée

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

	/**@brief Modifie le currPtr de manière à remonter dans le menu
	*/
	moveUp();

	/**@brief Modifie le currPtr de manière à descendre dans le menu
	*/
	moveDown();



};

#endif