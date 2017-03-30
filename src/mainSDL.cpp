
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>

#include "sdlGame.h"


using namespace std;




int main (int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO); // Démarrage de la SDL (ici : chargement du système vidéo)
    //Inserer la gestion d'erreur d'initialisation
    
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    /*
     La SDL est chargée.
     Vous pouvez mettre ici le contenu de votre programme
     */
    while(1){
        
    };
    
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
    
    return 0;
}
