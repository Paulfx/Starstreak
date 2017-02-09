#include "Image.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std;

//initialise le tab en 00 sans pixel 
Image::Image(){
	dimx=0;
	dimy=0;
}
//initialise le tab en X*Y avec 1 pointeur
Image::Image(const unsigned int X, const unsigned int Y){
	dimx=X;
	dimy=Y;
	tab=new Pixel[X*Y];
}
//destruction tableau case par case peut etre en commencant par la fin histoire de pas perdre le pointeur 
Image::~Image(){
	delete [] tab;
	dimx=0;
	dimy=0;
}
//Renvoie le pixel situé en (x,y) 
Pixel Image::getPix(const unsigned int x,const unsigned int y) const{

	assert(x>=0);
	assert(y>=0);
	assert(x<dimx);
	assert(y<dimy);
	//assert(tab[y*dimx+x]!=NULL);
	return tab[y*dimx+x];
}
//Remplace le pixel en (x,y) par le pixel passé en donnée // le pixel passé en donnée -> erreur d'accées, on doit le passer en D/R
void Image::setPix(const unsigned int x, const unsigned int y, Pixel couleur){ 
	assert(x<dimx);
	assert(y<dimy);
	//assert(tab[y*dimx+x]!=NULL); // utilité ? 
	tab[y*dimx+x].setRed(couleur.getRed());
	tab[y*dimx+x].setBlue(couleur.getBlue());
	tab[y*dimx+x].setGreen(couleur.getGreen());
}
//Dessine un rectangle sur l'image -> modifie tout les pixels situé entre les bornes  
void Image::dessinerRectangle (const int Xmin,const int Ymin,const int Xmax,const int Ymax,const Pixel couleur){

	assert(Xmin>=0);
	assert(Ymin>=0);
	assert(Xmax<dimx);
	assert(Ymax<dimy);
	for(int i=Xmin;i<Xmax;i++){
		for(int j=Ymin;j<Ymax;j++){
		
			setPix(i,j,couleur);
		}
	}
	
}
//Remplace tout les pixels de l'image par le pixel en donnée
void Image::effacer (const Pixel couleur){
	for (int i=0;i<dimx;i++){
		for(int j=0;j<dimy;j++){
			setPix(i,j,couleur);
		}
	}
}
// effectue une serie de test verifiant que le module fonctionne
/*void Image::testRegression(){
    cout << "test d'initialisation pour une grande image..." << endl;
    Image::initImage(9876,9876);
    assert (Image::dimx==9876);
    assert (Image::dimy==9876);
    //assert tab ??
    cout << "test grande image succes"<<endl;
    
    
    cout << "test d'initialisation pour une petite image..." << endl;
    Image::initImage(3,3);
    assert (Image::dimx==3);
    assert (Image::dimy==3);
    cout << "test petite image succes"<<endl;
}*/


/*void testRegression(){
    Image im1;
    
    cout << "test d'initialisation pour une grande image..." << endl;
    Image::initImage(9876,9876);
    assert (im1::dimx==9876);
    assert (im1::dimy==9876);
    //assert tab ??
    cout << "test grande image succes"<<endl;
    
    
    cout << "test d'initialisation pour une petite image..." << endl;
    Image::initImage(3,3);
    assert (im1::dimx==3);
    assert (im1::dimy==3);
    cout << "test petite image succes"<<endl;
    
}*/

void Image::testRegression() {
	Pixel a(0,0,0);
	Pixel b(1,0,0);
	Pixel c(2,0,0);
	dessinerRectangle(5,5,10,17,c);
	dessinConsole();
}

void Image::dessinConsole() const{

	for(int i=0;i<dimy;i++) {
		for(int j=0;j<dimx;j++) {
			Pixel px=getPix(i,j);
			switch(px.getRed()) {
				case 1:cout<<".";break;
				case 2:cout<<"#";break;
				default:cout<<"o";break;
			}
		}
		cout<<endl;
	}
}


