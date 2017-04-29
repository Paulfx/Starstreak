#include "class.h"

Note::Note() {}

Note::Note(unsigned int x, unsigned int y, unsigned int c, bool longBool, float speedNote) {
	posX = x;
	posY = y;
	color = c;
	longDuration = longBool;
	speed=speedNote;
}

unsigned int Note::getPosX() const {return posX;}
unsigned int Note::getPosY() const {return posY;}
unsigned int Note::getColor() const {return color;}
bool Note::getNeedPlay() const {return needPlay;}
bool Note::isPlayed() const {return played;}
bool Note::isLong() const {return longDuration;}
void Note::scroll(float delta) {posY+=delta*speed;}
void Note::setNeedPlay() {needPlay=true;}
void Note::setPlayed() {played=true;}