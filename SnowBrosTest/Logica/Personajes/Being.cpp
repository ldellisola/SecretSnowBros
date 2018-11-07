#include "Being.h"






Being::Being(uint16_t maxJumpTick, uint16_t maxWalkTick,uint16_t maxFallTicks, uint16_t x, uint16_t y, uint16_t ID)
	:maxWalkTick(maxWalkTick),maxJumpTick(maxJumpTick), maxFallTicks(maxFallTicks), xStart(x),yStart(y),
	ID(ID)
{
	horizontalState = BeingState::StillWalk;
	verticalState = BeingState::StillJump;
	resetHorizontalTicks();
	resetVerticalTicks();
	this->x = x;
	this->y = y;
}



void Being::kill()
{
	lives--;

	if (lives > 0) {
		this->x = xStart;
		this->y = yStart;
		this->horizontalState = BeingState::StillWalk;
		this->verticalState = BeingState::StillJump;
		resetHorizontalTicks();
		resetVerticalTicks();
	}
}

void Being::setMovement(BeingDirection dir)
{
	this->dir = dir;
}

void Being::setState(BeingState state)
{

	if (state == BeingState::Walking || state == BeingState::StillWalk) {
		this->horizontalState = state;
		resetHorizontalTicks();
	}

	else if ( state == BeingState::Falling || state == BeingState::StillJump) {
		this->verticalState = state;
		resetVerticalTicks();
	}
	else if (state == BeingState::Jumping && getVerticalState() != BeingState::Falling) {
		this->verticalState = state;
		resetVerticalTicks();
	}

}

void Being::resetVerticalTicks()
{
	verticalMovementTick = 0;
}

void Being::resetHorizontalTicks()
{
	horizontalMovementTick = 0;
}

void Being::updateVerticalTicks()
{
	if(getVerticalState() == BeingState::Falling)
		this->verticalMovementTick = (this->verticalMovementTick + 1) % maxFallTicks;
	else if(getVerticalState() == BeingState::Jumping)
		this->verticalMovementTick = (this->verticalMovementTick + 1) % maxJumpTick;
}

void Being::updateHorizontalTicks()
{
	this->horizontalMovementTick = (this->horizontalMovementTick + 1) % maxWalkTick;

}

void Being::setHorizontalState(BeingState state)
{
	horizontalState = state;
}

void Being::setVerticalState(BeingState state)
{
	verticalState = state;
}





