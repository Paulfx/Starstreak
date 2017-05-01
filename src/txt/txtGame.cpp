#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"
#include "txtGame.h"
#include <string>
#include "menu.h"



void diffAff(WinTXT & win, Menu & menu) {
	
	const unsigned int difficulty = menu.getDifficulty();

	win.clear();

    // Affichage des titres
	for(unsigned int i=0;i<menu.getNbSongs();++i) {
		const char* title = menu.getTitleSong(i).c_str();
		win.print(0,i,title);
	}
	
	//// partie difficultés //
	const unsigned int currI = menu.getCurrI();

	string diff = " 123";
	int taille = menu.getTitleSong(currI).size();
	win.print(taille,currI,diff.c_str()); //Affichage de la ligne difficulté
	win.print(taille+difficulty,currI+1,'*'); //Affichage de l'étoile sous la difficulté pointée
	win.draw();
}



void diffBoucle(WinTXT & win, Menu & menu) {

	bool ok = true;
	int c;

	do {
		diffAff(win,menu);

		#ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32

		c = win.getCh();
		switch (c) {
			case 'l':
				menu.increaseDiff();
				break;
			case 'j':
				menu.decreaseDiff();
				break;
			case 'm':
				/*menu.choose();	
				if(!menu.isActive()) { //On vérifie que le menu est inactif
					//gameBoucle(win,menu.getGame()); //Boucle qui fait tourner le jeu
					ok=false;
				}*/
				break;
			case 'q':
				ok = false;
				break;
		}

	} while (ok);
}



void menuAff(WinTXT & win, Menu & menu) {
	const unsigned int currI = menu.getCurrI();
	win.clear();
    // Affichage des titres
	for(unsigned int i=0;i<menu.getNbSongs();++i) {
		string titleStr = menu.getTitleSong(i);
		win.print(0,i,titleStr.c_str());
		string arrow = "<---";
		int taille = menu.getTitleSong(currI).size();
		win.print(taille,currI,arrow.c_str());
	}

	win.draw();
}


void menuBoucle (Menu& menu) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win(30,menu.getNbSongs()+10);

	bool ok = true;
	int c;

	do {
	    menuAff(win,menu);

        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32


		c = win.getCh();
		switch (c) {
			case 'i':
				menu.moveUp();
				break;
			case 'k':
				menu.moveDown();
				break;
			case 'm':
				diffBoucle(win,menu); //Boucle permettant le choix de la difficulté
				break;
			case 'q':
				ok = false;
				break;
		}

	} while (ok);

}




