#include "Jumper.h"





Jumper::Jumper(uint16_t y, uint16_t maxJumpTicks, uint16_t maxFallTicks)
	:MaxFallingTicks(maxFallTicks),MaxJumpingTicks(maxJumpTicks)
{
	this->verticalState = VerticalState::Still;
	this->resetVerticalTicks();
	this->setY(y);
}

Jumper::~Jumper()
{
}

void Jumper::update(void * ptr)
{
	if (getVerticalState() != VerticalState::Still)
		updateVerticalTicks();

	char * column = (char*)ptr;

	switch (getVerticalState())
	{
	case VerticalState::Still:
		if ((column[y + 1] == 'E' || column[y] == 'F')) {
			this->setVerticalState(VerticalState::Falling);
			resetVerticalTicks();
		}
		break;
	case VerticalState::Jumping:
		break;
	case VerticalState::Falling:
		break;
	default:
		break;
	}



}

case BeingState::Jumping:
	if (getVerticalTicks() == maxJumpTick / 2) {
		if ((this->y - 1) >= 0) {
			y--;
		}
	}
	else if (getVerticalTicks() == maxJumpTick - 1) {
		if ((this->y - 1) >= 0) {
			y--;

		}

		this->setState(BeingState::StillJump);
		resetVerticalTicks();
	}
	break;
case BeingState::Falling:
	if (getVerticalTicks() == maxFallTicks - 1) {
		y++;
		if (y + 1 < map.fila && map.map[y + 1][x] == 'F') {
			this->setState(BeingState::StillJump);
		}

		this->resetVerticalTicks();
	}
	break;

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

VerticalState Jumper::getVerticalState()
{
	return verticalState;
}

void Jumper::setY(uint16_t y)
{
	this->y = y;
}

uint16_t Jumper::getY()
{
	return y;
}
