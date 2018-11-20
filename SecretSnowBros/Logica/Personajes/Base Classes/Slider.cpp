#include "Slider.h"



Slider::Slider(uint16_t x, uint16_t maxHorizontalTicks)
	:MaxHorizontalTicks(maxHorizontalTicks)
{
	this->setHorizontalDir(HorizontalDirection::Right);
	this->resetHorizontalTicks();
	this->setHorizontalState(HorizontalState::Still);
	this->setX(x);
}


Slider::~Slider()
{
}

void Slider::update(void * ptr)
{
	char* map = (char *)ptr;

	if (getHorizontalState() != HorizontalState::Still)
		updateHorizontalTicks();
	
	switch (horizontalState)
	{
	case HorizontalState::Still:
		break;
	case HorizontalState::Moving:

		if (this->getHorizontalTicks() == this->MaxHorizontalTicks) {
			
			if (this->getHorizontalDir() == HorizontalDirection::Left)
				if (x - 1 >= 0 && map[x - 1] != 'F')
					this->x--;
				else {
					setHorizontalDir(HorizontalDirection::Right);
				}
			else if (this->getHorizontalDir() == HorizontalDirection::Right)
				if (map[x + 1] != 'F')
					this->x++;
				else
					setHorizontalDir(HorizontalDirection::Left);
			this->resetHorizontalTicks();

		}
		break;
	}


}

void Slider::updateHorizontalTicks()
{
	horizontalTicks++;
}

void Slider::resetHorizontalTicks()
{
	horizontalTicks = 0;
}

uint16_t Slider::getHorizontalTicks()
{
	return horizontalTicks;
}

void Slider::setHorizontalDir(HorizontalDirection dir)
{
	this->horizontalDir = dir;
}

HorizontalDirection Slider::getHorizontalDir()
{
	return horizontalDir;
}

void Slider::setHorizontalState(HorizontalState state)
{
	this->horizontalState = state;
}

HorizontalState Slider::getHorizontalState()
{
	return horizontalState;
}

void Slider::setX(uint16_t x)
{
	this->x = x;
}

uint16_t Slider::getX()
{
	return x;
}
