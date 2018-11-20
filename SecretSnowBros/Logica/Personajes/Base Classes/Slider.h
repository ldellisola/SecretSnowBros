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

class Slider
{
public:
	Slider(uint16_t x, uint16_t maxHorizontalTicks);
	virtual ~Slider();

	virtual void update(void*ptr);

	void setHorizontalDir(HorizontalDirection dir);

	HorizontalDirection getHorizontalDir();

	uint16_t getX();

protected:
	void updateHorizontalTicks();

	void resetHorizontalTicks();


	uint16_t getHorizontalTicks();



	void setHorizontalState(HorizontalState state);

	HorizontalState getHorizontalState();

	void setX(uint16_t x);





private:
	const uint16_t MaxHorizontalTicks;

	uint16_t x, horizontalTicks;

	HorizontalState horizontalState;

	HorizontalDirection horizontalDir;
};

