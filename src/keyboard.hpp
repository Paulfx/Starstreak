//
//  Keyboard.hpp
//  
//
//  Created by Rabut Théo on 21/03/2017.
//
//

#ifndef keyboard_hpp
#define keyboard_hpp

#include <stdio.h>


enum enumPress {noPress, simplePress, longPress}; 


//le keyboard est un tableau de enumPress, noPress si la touche est libre, simplePress si la touche vient d'être enfoncée, 
// longPress si la touche est enfoncée depuis plus de 2 itérations

class keyboard{
    private :

    enumPress* keyTab; //0 -> enter, [1->5] -> note "AZERT"

    public :
    
    /** @brief Constructeur
     */
    
    keyboard();
    
    /** @brief Destructeur 
     */
    ~keyboard();
    
    
    /** @brief Mutateur d'etat avec position de l'element
     @param i position de l'etat a modifié
     */
    void setKey(const unsigned int i);
    
    /** @brief Accesseur du tableau d'etat
     renvoie un pointeur sur tableau de bool
    */
    bool* getKey() const;


    bool isNoPress() const;

    bool isSimplePress() const;

    bool isLongPress() const;



};


#endif /* Keyboard_hpp */
