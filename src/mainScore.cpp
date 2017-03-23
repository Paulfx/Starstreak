#include "score.h"
#include "partition.h"
#include "keyboard.hpp"

int main(){
    Score test (30);
    
    line lineTest;
    lineTest.data="01010";
    //line.time=34.0;
    
    keyboard ktest;
    ktest.setKey(0);
    ktest.setKey(2);
    ktest.setKey(4);
    test.updateScore(lineTest,ktest);
}


//g++ –o score src/mainScore.cpp src/score.cpp -lm
