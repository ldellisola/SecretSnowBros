#include "Being.h"






Being::Being(uint16_t maxJumpTick, uint16_t maxWalkTick,uint16_t maxFallTicks, uint16_t x, uint16_t y, uint16_t ID)
	: Slider(x,maxWalkTick),Jumper(y,maxJumpTick,maxFallTicks), xStart(x),yStart(y),ID(ID)
{
	this->setState(BeingState::StillJump);
	this->setState(BeingState::StillWalk);

}



void Being::kill()
{


	if (lives > 0) {
		lives--;
	}
	else {
		Jumper::setVerticalState(VerticalState::Still);
		Slider::setHorizontalState(HorizontalState::Still);
		resetHorizontalTicks();
		resetVerticalTicks();
	}
}

void Being::revive()
{
	this->lives = 1;
}


void Being::setState(BeingState state)
{
	
	if (state == BeingState::WalkingLeft ) {
		Slider::setHorizontalState(HorizontalState::Moving);
		setHorizontalDir(HorizontalDirection::Left);
	}
	else if (state == BeingState::WalkingRight) {
		Slider::setHorizontalState(HorizontalState::Moving);
		setHorizontalDir(HorizontalDirection::Right);
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

	this->beingState = state;
	
}


BeingState Being::getState() {
	return beingState;
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

}


void Being::collition(Projectile * proy)
{
	if (proy->getX() == this->getX() && proy->getY() == this->getY()) {
		this->kill();
	}
}



