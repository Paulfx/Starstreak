#include <iostream>
#include "Pixel.h"

using namespace std;


//constructeur par default pixel noir
Pixel::Pixel(){
	R=0;
	G=0;
	B=0;
}
//constructeur par parametres
Pixel::Pixel(const unsigned char Red,const unsigned char Green,const unsigned char Blue){
	R=Red;
	G=Green;
	B=Blue;
}
// Accesseur : récupère la composante rouge du pixel
unsigned char Pixel::getRed(){
	return R;
}
// Accesseur : récupère la composante verte du pixel
unsigned char Pixel::getGreen(){
	return G;
}
// Accesseur : récupère la composante bleue du pixel
unsigned char Pixel::getBlue(){
	return B;
}
// Mutateur : modifie la composante rouge du pixel
void Pixel::setRed (unsigned char newRed){
	R=newRed;
}   
// Mutateur : modifie la composante verte du pixel
void Pixel::setGreen (unsigned char newGreen){
	G=newGreen;
}
// Mutateur : modifie la composante bleue du pixel
void Pixel::setBlue (unsigned char newBlue){
	B=newBlue;
}


