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


	if (lives > 0) {
		lives--;
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
	else if (state == BeingState::Jumping && getVerticalState() == BeingState::StillJump) {
		this->verticalState = state;
		resetVerticalTicks();
	}
	else if ( state == BeingState::Falling || state == BeingState::StillJump) {
		this->verticalState = state;
		resetVerticalTicks();
	}
	//else if (state == BeingState::Jumping && getVerticalState() != BeingState::Falling && getVerticalState() == BeingState::Jumping) {
	//	this->verticalState = state;
	//	resetVerticalTicks();
	//}

}

void Being::update(void * ptr)
{
	World& map = *(World *)ptr;

	if (getVerticalState() != BeingState::StillJump)
		updateVerticalTicks();
	if (getHorizontalState() != BeingState::StillWalk)
		updateHorizontalTicks();



	switch (getVerticalState())
	{

	case BeingState::StillJump:
		if (y + 1 < map.fila && (map.map[y + 1][x] == 'E' || map.map[y][x] == 'F')) {
			this->setState(BeingState::Falling);
			resetVerticalTicks();
		}
		break;
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

	switch (getHorizontalState())
	{
	case BeingState::StillWalk:
		break;
	case BeingState::Walking:
		if (this->getHorizontalTicks() == this->maxWalkTick - 1) {
			if ((y + 1 < map.fila && map.map[y + 1][x] == 'E') && getVerticalState() == BeingState::StillJump) {

				setState(BeingState::Falling);
			}
			if (this->getDirection() == BeingDirection::Left && x - 1 >= 0 && map.map[y][x - 1] != 'F')
				this->x--;
			else if (this->getDirection() == BeingDirection::Right && x + 1 < map.columna && map.map[y][x + 1] != 'F')
				this->x++;
			this->resetHorizontalTicks();

		}
		break;
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
		this->verticalMovementTick = (this->verticalMovementTick + 1) ;
	else if(getVerticalState() == BeingState::Jumping)
		this->verticalMovementTick = (this->verticalMovementTick + 1) ;
}

void Being::updateHorizontalTicks()
{
	this->horizontalMovementTick = (this->horizontalMovementTick + 1) ;

}

void Being::setHorizontalState(BeingState state)
{
	horizontalState = state;
}

void Being::setVerticalState(BeingState state)
{
	verticalState = state;
}





