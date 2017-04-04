
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>

#include "sdlGame.h"


using namespace std;




int main (int argc, char *argv[]){
    sdlGame mySDL;
    mySDL.init_Window();
    mySDL.open_Window();
    SDL_Delay(10000);
    
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
    
    return 0;
}
