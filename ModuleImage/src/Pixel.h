#ifndef PIXEL_H
#define PIXEL_H
#include <iostream>

using namespace std;

class Pixel {
private: 
	unsigned char R;
	unsigned char G;
	unsigned char B;
public:
	//constructeur par default pixel noir
	Pixel();
	//constructeur par parametres
	Pixel(const unsigned char R,const unsigned char G,const unsigned char B);
	// Accesseur : récupère la composante rouge du pixel
	unsigned char getRed(); 
	// Accesseur : récupère la composante verte du pixel
	unsigned char getGreen();
	// Accesseur : récupère la composante bleue du pixel
	unsigned char getBlue();
	// Mutateur : modifie la composante rouge du pixel
	void setRed (unsigned char newRed);   
	// Mutateur : modifie la composante verte du pixel
	void setGreen (unsigned char newGreen);
	// Mutateur : modifie la composante bleue du pixel
	void setBlue (unsigned char newBlue);
};


#endif