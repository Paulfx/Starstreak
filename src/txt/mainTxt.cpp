#include "winTxt.h"
#include "txtGame.h"
#include "menu.h"

int main ( int argc, char** argv ) {
    termClear();
	Menu menu("../data/index");
	menuBoucle(menu);
    termClear();
	return 0;
}



