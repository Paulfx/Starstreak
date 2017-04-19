
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>

#include "sdlGame.h"


using namespace std;




int main (int argc, char *argv[]){
    /*
    int flags=MIX_INIT_OGG|MIX_INIT_MOD;
    int initted=Mix_Init(flags);
    SDL_INIT_AUDIO;
    int Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,wav, channels,  chunksize);
    //frequency, default est bonne (22050 hz) -> frequence CD=44100, mais limité par la puissance 
    //format output sample format
    //channels Nombre de channel de son en sortie (periphérique?) -> 2 stereo, 1 mono, rien a voir avec les channel de mixing
    //chunksize, used per output sample
    */
    sdlGame mySDL;
    while(1){
        SDL_Delay(100);
    }

    
    
    
    mySDL.~sdlGame(); // destructeur ?
    return 0;
    
}
