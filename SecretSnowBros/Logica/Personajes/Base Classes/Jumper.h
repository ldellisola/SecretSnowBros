#pragma once
#include <stdint.h>
//Class that moves vertically
enum class VerticalState
{
	Still, Jumping, Falling
};

/*
	This class allows the child to move up and down following the rules of the map
*/
class Jumper
{
public:

	Jumper(uint16_t y, uint16_t maxJumpTicks, uint16_t maxFallTicks);
	virtual ~Jumper();

	// it updates the position, it should be called once per tick and the pointer should be to a array of chars
	// that represents the vertical column
	virtual void update(void * ptr);

	uint16_t getY();
	void setY(uint16_t y);

protected:

	void updateVerticalTicks();
	void resetVerticalTicks();
	uint16_t getVerticalTicks();

	void setVerticalState(VerticalState state);
	VerticalState getVerticalState();


	const uint16_t MaxJumpingTicks;
	const uint16_t MaxFallingTicks;

private:

	uint16_t y, verticalTicks;
	VerticalState verticalState;
};
