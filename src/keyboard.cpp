//
//  Keyboard.cpp
//  
//
//  Created by Rabut Théo on 21/03/2017.
//
//

#include "keyboard.hpp"


keyboard::keyboard(){
    keyTab=new enumPress[6];
    for(int i=0;i<6;i++){
        keyTab[i]=noPress;
    }
}

keyboard::~keyboard(){
    delete [] keyTab;
}



void keyboard::setKey(const unsigned int i){
    if(keyTab[i]){
        keyTab[i]=false;
    }else{
        keyTab[i]=true;
    }
}


bool* keyboard::getKey() const{
    return keyTab;
}


bool isNoPress(i) const { 
    if(keyTab[i] == noPress) return true;
    return false; 
}

bool isSimplePress(i) const {
    if(keyTab[i] == simplePress) return true;
    return false;
}

bool isLongPress(i) const {
    if(keyTab[i] == longPress) return true;
    return false;
}

void setNoPress(i) { keyTab[i] = noPress; }

void setSimplePress(i) { keyTab[i] = noPress; }

void setLongPress(i) { keyTab[i] = noPress; }