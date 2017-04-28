#include "class.h"

Note::Note() {}

Note::Note(int x, int y, int c, bool longBool, float speedNote) {
	posX = x;
	posY = y;
	color = c;
	longDuration = longBool;
	speed=speedNote;
}

int Note::getPosX() const {return posX;}
int Note::getPosY() const {return posY;}
int Note::getColor() const {return color;}
bool Note::getNeedPlay() const {return needPlay;}
bool Note::isPlayed() const {return played;}
bool Note::isLong() const {return longDuration;}
void Note::scroll(float delta) {posY+=delta*speed;}
void Note::setNeedPlay() {needPlay=true;}
void Note::setPlayed() {played=true;}