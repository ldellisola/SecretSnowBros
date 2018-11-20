#pragma once
#include "MVC/Observer.h"
#include <stdint.h>

#include <AllwAnimation/AllegroSprite.h>


class SnowBallObserver :public Observer
{
public:
	SnowBallObserver(std::string file, uint16_t boxWidth, uint16_t boxHeight) {
		sprite = new AllegroSprite(file, boxHeight, boxWidth);
	}
	~SnowBallObserver() {
		delete sprite;
	}
	void draw(void * ptr) {

	}
private:

	AllegroSprite * sprite = nullptr;
};

