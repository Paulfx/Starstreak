#ifndef TERRAIN_H
#define TERRAIN_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <partition.h>
#include <jeu.h>
#include <score.h>

/**
 @brief la classe qui teste le succés d'une note et modifie le score
 */

class TerrAin {
    
private:
    Partition part;
    line tab[//depend de la difficulté][8];
    float score;
    
    
public:
    Terrain();
    
    Terrain(   );
};
