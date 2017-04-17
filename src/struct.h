#ifndef STRUCT_H
#define STRUCT_H

#include <string>


typedef struct {
	string title,filePartition,fileMusic,fileImage;
	float duration;
} Song;

typedef struct { //Une ligne de jeu = données (eg "1001") + temps jusqu'à la prochaine ligne
	string data; 
	float time;
    //bool onSequence;
} line;


#endif