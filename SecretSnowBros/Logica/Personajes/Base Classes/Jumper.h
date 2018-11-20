#pragma once
#include <stdint.h>

enum class VerticalState
{
	Still, Jumping, Falling
};
class Jumper
{
public:
	Jumper(uint16_t y, uint16_t maxJumpTicks, uint16_t maxFallTicks);
	virtual ~Jumper();

	virtual void update(void * ptr);
	uint16_t getY();

protected:

	void updateVerticalTicks();
	void resetVerticalTicks();
	uint16_t getVerticalTicks();

	void setVerticalState(VerticalState state);
	VerticalState getVerticalState();

	void setY(uint16_t y);

	const uint16_t MaxJumpingTicks;
	const uint16_t MaxFallingTicks;

private:

	uint16_t y, verticalTicks;
	VerticalState verticalState;
};
