#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "Pixel.h"

class Image {
    
private:
    Pixel *tab;
    unsigned int dimx;
    unsigned int dimy;
    
    
public:
    //initialise le tab en 00;
	Image();
    //initialise le tab en x*y avec un pointeur 
    Image(const int X, const int Y);
    //destruction tableau case par case peut etre en commencant par la fin histoire de pas perdre le pointeur 
    ~Image();
    //Renvoie le pixel situé en (x,y) 
    Pixel getPix(const int x,const int y) const;
    //Remplace le pixel en (x,y) par le pixel passé en donnée 
    void setPix(const unsigned int x, const unsigned int y,const Pixel couleur); 
    //Dessine un rectangle sur l'image -> modifie tout les pixels situé entre les bornes  
    void dessinerRectangle (const int Xmin,const int Ymin,const int Xmax,const int Ymax,const Pixel couleur);
    //Remplace tout les pixels de l'image par le pixel en donnée
    void effacer (const Pixel couleur);
    // effectue une serie de test verifiant que le module fonctionne
    void testRegression();

    void dessinConsole() const;

    void Image::sauver(const string & filename) const;

    void Image::ouvrir(const string & filename);

    void Image::afficherConsole();
    
};

