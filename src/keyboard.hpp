//
//  Keyboard.hpp
//  
//
//  Created by Rabut Théo on 21/03/2017.
//
//

#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <stdio.h>
//le keyboard est un tableau de booleen, false la touche est libre, true la touche est enfoncé
//0 -> enter, [1->5] -> note "AZERT"
class keyboard{
    private :
    bool* keyTab;
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
    bool* getKey();




};


#endif /* Keyboard_hpp */
