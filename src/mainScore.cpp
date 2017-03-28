#include "score.h"
#include "partition.h"
#include "keyboard.hpp"

int main(){
    /*Menu menu("../data/index");
    menu.afficher();
    menu.choose();
    return 0;
    */
    
    Score test (30);
    
    line lineTest;
    lineTest.data="01010";
    //line.time=34.0;
    
    
    
    line lineTestFail;
    lineTestFail.data="00010";
    
    keyboard ktest;
    ktest.setKey(0);
    ktest.setKey(2);
    ktest.setKey(4);
    
    
    
    /*test.updateScore(lineTest,ktest);
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
