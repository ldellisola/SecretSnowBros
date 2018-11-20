#include "Being.h"






Being::Being(uint16_t maxJumpTick, uint16_t maxWalkTick,uint16_t maxFallTicks, uint16_t x, uint16_t y, uint16_t ID)
	: Slider(x,maxWalkTick),Jumper(y,maxJumpTick,maxFallTicks), xStart(x),yStart(y),ID(ID)
{

}



void Being::kill()
{


	if (lives > 0) {
		lives--;
		Jumper::setY(yStart);
		Slider::setX(xStart);
		//this->x = xStart;
		//this->y = yStart;
		Jumper::setVerticalState(VerticalState::Still);
		Slider::setHorizontalState(HorizontalState::Still);
		//this->horizontalState = BeingState::StillWalk;
		//this->verticalState = BeingState::StillJump;
		resetHorizontalTicks();
		resetVerticalTicks();
	}
}

//void Being::setMovement(BeingDirection dir)
//{
//
//
//	//this->dir = dir;
//}

void Being::setState(BeingState state)
{
	if (state == BeingState::Walking ) {
		Slider::setHorizontalState(HorizontalState::Moving);
	}
	else if (state == BeingState::StillWalk) {
		Slider::setHorizontalState(HorizontalState::Still);
	}
	else if (state == BeingState::Jumping) {
		Jumper::setVerticalState(VerticalState::Jumping);
	}
	else if ( state == BeingState::Falling) {
		Jumper::setVerticalState(VerticalState::Falling);
	}
	else if (state == BeingState::StillJump)
		Jumper::setVerticalState(VerticalState::Still);
	//if (state == BeingState::Walking || state == BeingState::StillWalk) {
	//	Slider::setHorizontalState(HorizontalState::Moving);
	//	//this->horizontalState = state;
	//	//resetHorizontalTicks();
	//}
	//else if (state == BeingState::Jumping && getVerticalState() == BeingState::StillJump) {
	//	this->verticalState = state;
	//	resetVerticalTicks();
	//}
	//else if ( state == BeingState::Falling || state == BeingState::StillJump) {
	//	this->verticalState = state;
	//	resetVerticalTicks();
	//}
	////else if (state == BeingState::Jumping && getVerticalState() != BeingState::Falling && getVerticalState() == BeingState::Jumping) {
	////	this->verticalState = state;
	////	resetVerticalTicks();
	////}

}

void Being::update(void * ptr)
{
	World& map = *(World *)ptr;

	
	std::unique_ptr<char> row(new char[map.columna]);

	for (int i = 0; i < map.columna; i++) {
		row.get()[i] = map.map[getY()][i];
	}

	Slider::update(row.get());

	std::unique_ptr<char> column(new char[map.fila]);

	for (int i = 0; i < map.fila; i++) {
		column.get()[i] = map.map[i][getX()];
	}

	Jumper::update(column.get());

	/*if (getVerticalState() != BeingState::StillJump)
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
			if (this->getDirection() == BeingDirection::Left)
				if (x - 1 >= 0 && map.map[y][x - 1] != 'F')
					this->x--;
				else {
					setMovement(BeingDirection::Right);
				}
			else if (this->getDirection() == BeingDirection::Right)
				if (x + 1 < map.columna && map.map[y][x + 1] != 'F')
					this->x++;
				else
					setMovement(BeingDirection::Left);
			this->resetHorizontalTicks();

		}
		break;
	}*/
}
//
//void Being::resetVerticalTicks()
//{
//	verticalMovementTick = 0;
//}
//
//void Being::resetHorizontalTicks()
//{
//	horizontalMovementTick = 0;
//}
//
//void Being::updateVerticalTicks()
//{
//	if(getVerticalState() == BeingState::Falling)
//		this->verticalMovementTick = (this->verticalMovementTick + 1) ;
//	else if(getVerticalState() == BeingState::Jumping)
//		this->verticalMovementTick = (this->verticalMovementTick + 1) ;
//}
//
//void Being::updateHorizontalTicks()
//{
//	this->horizontalMovementTick = (this->horizontalMovementTick + 1) ;
//
//}
//
//void Being::setHorizontalState(BeingState state)
//{
//	horizontalState = state;
//}
//
//void Being::setVerticalState(BeingState state)
//{
//	verticalState = state;
//}





