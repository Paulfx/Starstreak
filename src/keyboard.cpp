//
//  Keyboard.cpp
//  
//
//  Created by Rabut Théo on 21/03/2017.
//
//

#include "keyboard.hpp"


keyboard::keyboard(){
    keyTab=new bool[6];
    for(int i=0;i<6;i++){
        keyTab[i]=false;
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
