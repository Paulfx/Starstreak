//
//  Keyboard.hpp
//  
//
//  Created by Rabut Théo on 21/03/2017.
//
//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>


enum enumPress {noPress, simplePress, longPress}; 


//le keyboard est un tableau de enumPress, noPress si la touche est libre, simplePress si la touche vient d'être enfoncée, 
// longPress si la touche est enfoncée depuis plus de 2 itérations

class Keyboard{

private :

    enumPress* keyTab; //[0->4] -> note "AZERT"
    bool validation; //True si la touche de validation a été enfoncée, false sinon

public :
    
    /** @brief Constructeur de la classe Keyboard
     */
    Keyboard();
    
    /** @brief Destructeur 
     */
    ~Keyboard();
    
    /** @brief Accesseur
    Renvoie true si la touche "i" est enfoncée
    */
    bool isNoPress(unsigned int i) const;
    
    /** @brief Accesseur
    */    
    bool isSimplePress(unsigned int i) const;
    
    /** @brief Accesseur
    */
    bool isLongPress(unsigned int i) const;

    /** @brief Accesseur
    */
    bool isValid() const;
    
    /** @brief Mutateur
    */
    void setNoPress(unsigned int i);

    /** @brief Mutateur
    Initialise tout le tableau à noPress
    */
    void clear();
    
    /** @brief Mutateur
    Met la touche 'i' à simplePress si elle était à noPress, longPress sinon
    */
    void setPress(unsigned int i);
    
    /** @brief Mutateur
    */
    void setValid(bool b);

    void afficher();

    /** Transforme tous les simplePress en longPress
    */
    void setLongPressAllSimplePress(); 

};


#endif /* KEYBOARD_H*/
