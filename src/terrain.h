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

class Terrain {
    
private:
    Partition part;
    int difficulty;
    char** terrain;
    string data;//element à place dans un case de terrain
    in nbLine;//nombre de case utilisée dans le terrain (utile lors de la construction)
    
    
public:
    Terrain();
    
    Terrain(const ligne & ,int difficulty,);
};
