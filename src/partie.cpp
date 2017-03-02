#include "partie.cpp"

using namespace std;

Partie::Partie(){
    Partition();
    score=0;
    noteStreak=0;
    startPower=0;
}

Partie::Partie(const string & filename,int difficulty){
    Partition(const string & filename,int difficulty);
    score=0;
    noteStreak=0;
    startPower=0;
}

Partie::~Partie(){
    ~Partition();
    score=0;
    noteStreak=0;
    startPower=0;
    
}
