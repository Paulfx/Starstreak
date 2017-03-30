#include "score.h"
#include "menu.h"
#include "partition.h"
#include "keyboard.hpp"

int main(){
    keyboard ktest;
    ktest.setKey(0);
    ktest.setKey(2);
    ktest.setKey(4);
    Menu menu("../data/index");
    menu.afficher();
    menu.choose();
    
    //Score test (30);
    
    //line lineTest;
    //lineTest.data="01010";
    //line.time=34.0;
    
    
    
    //line lineTestFail;
    //lineTestFail.data="00010";
    
    
    
    /*
    
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTest,ktest);
    
    test.updateScore(lineTestFail,ktest);
    
    test.updateScore(lineTest,ktest);
    test.updateScore(lineTestFail,ktest);
    
    
    return 0;*/
}
