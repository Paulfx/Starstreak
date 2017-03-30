//
//  Keyboard.cpp
//  
//
//  Created by Rabut Théo on 21/03/2017.
//
//

#include "keyboard.hpp"


Keyboard::Keyboard(){
    keyTab=new enumPress[6];
    for(int i=0;i<6;i++){
        keyTab[i]=noPress;
    }
    validation = false;
}

Keyboard::~Keyboard(){
    delete [] keyTab;
}

bool Keyboard::isNoPress(unsigned int i) const { 
    if(keyTab[i] == noPress) return true;
    return false; 
}

bool Keyboard::isSimplePress(unsigned int i) const {
    if(keyTab[i] == simplePress) return true;
    return false;
}

bool Keyboard::isLongPress(unsigned int i) const {
    if(keyTab[i] == longPress) return true;
    return false;
}

bool Keyboard::isValid() const {return validation;}

void Keyboard::setNoPress(unsigned int i) { keyTab[i] = noPress; }

void Keyboard::setSimplePress(unsigned int i) { keyTab[i] = noPress; }

void Keyboard::setLongPress(unsigned int i) { keyTab[i] = noPress; }

void Keyboard::setValid(bool b) { validation = b; }