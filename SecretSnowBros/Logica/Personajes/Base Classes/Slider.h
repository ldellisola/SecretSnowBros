#pragma once
#include <stdint.h>
#include "Logica/juego/Cmap.h"

enum class HorizontalState
{
	Moving, Still
};

enum class HorizontalDirection
{
	Left, Right
};
/*
	This class allows its child to move freely in a horizontal line according to the map
*/
class Slider
{
public:
	Slider(uint16_t x, uint16_t maxHorizontalTicks);
	virtual ~Slider();

	// It updates the position of the Slider every tick. It recieves a pointer to an array of chars that represent the 
	// horizontal row in which the Slider is.
	virtual void update(void*ptr);

	void setHorizontalDir(HorizontalDirection dir);

	HorizontalDirection getHorizontalDir();

	void setHorizontalState(HorizontalState state);

	void setX(uint16_t x);

	uint16_t getX();

protected:
	void updateHorizontalTicks();

	void resetHorizontalTicks();

	uint16_t getHorizontalTicks();

	HorizontalState getHorizontalState();

private:
	const uint16_t MaxHorizontalTicks;

	uint16_t x, horizontalTicks;

	HorizontalState horizontalState;

	HorizontalDirection horizontalDir;
};

