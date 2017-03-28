#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include <string>
#include "menu.h"
#include "struct.h"

void txtAff(WinTXT & win, Menu & menu) {
	Song** songList = menu.getSongTab();
	const unsigned int currI = menu.getCurrI();

	win.clear();

    // Affichage des titres
	for(unsigned int i=0;i<menu.getNbSongs();++i) {
		const char* title = songList[i]->title.c_str();
		win.print(0,i,title);
		string arrow = "<---";
		int taille = songList[currI]->title.size();
		win.print(taille,currI,arrow.c_str());
	}

	win.draw();
}


void diffAff(WinTXT & win, Menu & menu) {
	
	Song** songList = menu.getSongTab();
	const unsigned int difficulty = menu.getDifficulty();


	win.clear();

    // Affichage des titres
	for(unsigned int i=0;i<menu.getNbSongs();++i) {
		const char* title = songList[i]->title.c_str();
		win.print(0,i,title);
	}
	
	//// partie difficultés //

	const unsigned int currI = menu.getCurrI();

	string diff = " 123";
	int taille = songList[currI]->title.size();
	win.print(taille,currI,diff.c_str());


	win.print(taille+difficulty,currI+1,'*');


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
				menu.choose();
				break;
			case 'q':
				ok = false;
				break;
		}

	} while (ok);

}



void txtBoucle (Menu& menu) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win (30,menu.getNbSongs()+10);

	bool ok = true;
	int c;

	do {
	    txtAff(win,menu);

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

				diffBoucle(win,menu);

				menu.choose();
				break;
			case 'q':
				ok = false;
				break;
		}

	} while (ok);

}
