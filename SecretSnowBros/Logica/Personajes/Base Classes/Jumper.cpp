#include "Jumper.h"


Jumper::Jumper(uint16_t y, uint16_t maxJumpTicks, uint16_t maxFallTicks)
	:MaxFallingTicks(maxFallTicks),MaxJumpingTicks(maxJumpTicks)
{
	this->verticalState = VerticalState::Still;
	this->resetVerticalTicks();
	this->setY(y);
}

Jumper::~Jumper(){
}

void Jumper::update(void * ptr)
{
	if (getVerticalState() != VerticalState::Still) 
		updateVerticalTicks();

	char * column = (char*)ptr;

	if (getVerticalState() == VerticalState::Still && column[y + 1] == 'E') {//si estoy quieto y abajo hay aire debo caer
		this->setVerticalState(VerticalState::Falling);
	}

	switch (getVerticalState())
	{
	case VerticalState::Still:
		if ((column[y + 1] == 'E' || column[y] == 'F')) {
			this->setVerticalState(VerticalState::Falling);
			resetVerticalTicks();
		}
		break;
	case VerticalState::Jumping:
		if (getVerticalTicks() == MaxJumpingTicks / 2) {
			if ((this->y - 1) >= 0) 
				y--;
		}
		else if (getVerticalTicks() == MaxJumpingTicks-1 ) {
			if ((this->y - 1) >= 0) 
				y--;

			setVerticalState(VerticalState::Still);
			resetVerticalTicks();
			}
		break;
	case VerticalState::Falling:
		if (getVerticalTicks() == MaxFallingTicks - 1) {
			
			if (column[y + 1] == 'F' && column[y] == 'E') {
				setVerticalState(VerticalState::Still);
			}
			else
				y++;

			this->resetVerticalTicks();
		}
		break;
	default:
		break;
	}



}


void Jumper::updateVerticalTicks()
{
	verticalTicks++;
}

void Jumper::resetVerticalTicks()
{
	verticalTicks = 0;
}

uint16_t Jumper::getVerticalTicks()
{
	return verticalTicks;
}

void Jumper::setVerticalState(VerticalState state)
{
	if (state == VerticalState::Jumping && getVerticalState() == VerticalState::Still) {
		this->verticalState = state;
		resetVerticalTicks();
	}
	else if (state == VerticalState::Falling || state == VerticalState::Still) {
		verticalState = state;
		resetVerticalTicks();
	}
}

VerticalState Jumper::getVerticalState() {return verticalState;}

void Jumper::setY(uint16_t y) {this->y = y;}

uint16_t Jumper::getY() {return y;}
