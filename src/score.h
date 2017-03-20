#ifndef SCORE_H
#define SCORE_H


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

class Score {
    
    private :
    
    int totalScore;
    int noteStreak;
    bool starPower;
    int numberSucces;
    
public:
    
    Score();
    
    ~Score();
    
    void updateScore();
    

}
