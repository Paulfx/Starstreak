#include "keyboard.h"
#include <cassert>
#include <iostream>


const unsigned int LIMIT_NUMBER_FRAMES = 10;

Keyboard::Keyboard(){
    keyTab=new enumPress[5];
    numberFramesPressedTab=new unsigned int[5];
    clear();
    validation = false;
}

Keyboard::~Keyboard(){
    delete [] keyTab;
    delete [] numberFramesPressedTab;
}

bool Keyboard::isNoPress(unsigned int i) const {
    assert(i<5);
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

void Keyboard::setNoPress(unsigned int i) { keyTab[i] = noPress; numberFramesPressedTab[i]=0; }

void Keyboard::clear() {
    for(int i=0;i<5;i++){
        keyTab[i]=noPress;
        numberFramesPressedTab[i]=0;
    }
}

void Keyboard::setPress(unsigned int i) { 
    if(keyTab[i] == noPress) keyTab[i] = simplePress;
    else if(numberFramesPressedTab[i] < LIMIT_NUMBER_FRAMES) numberFramesPressedTab[i]++;
    else keyTab[i] = longPress; 
}

void Keyboard::setValid(bool b) { validation = b; }

void Keyboard::afficher() {
    
    for(int i=0;i<5;i++){
        std::cout<<keyTab[i];
    }
    std::cout<<std::endl;
}

std::string Keyboard::getCurrentStateStr() {
    std::string res;
    for(int i=0;i<5;++i) {
        res+=std::to_string(keyTab[i]);
    }
    return res;
}

void Keyboard::setLongPressAllSimplePress() {
    for(int i=0;i<5;i++){
        if(keyTab[i]==simplePress) keyTab[i]=longPress;
    }
}