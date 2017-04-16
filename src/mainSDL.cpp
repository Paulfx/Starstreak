
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>

#include "sdlGame.h"


using namespace std;




int main (int argc, char *argv[]){
    
    int flags=MIX_INIT_OGG|MIX_INIT_MOD;
    int initted=Mix_Init(flags);
    SDL_INIT_AUDIO
    int Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,wav, int channels, int chunksize);
    //frequency, default est bonne (22050 hz) -> frequence CD=44100, mais limité par la puissance 
    //format output sample format
    //channels Nombre de channel de son en sortie (periphérique?) -> 2 stereo, 1 mono, rien a voir avec les channel de mixing
    //chunksize, used per output sample
    
    sdlGame mySDL;
    mySDL.init_Window();
    mySDL.open_Window();
    
    while(1){
        SDL_Delay(10000);
    }

    
    
    
    
    IMG_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
    
    return 0;
    
}
