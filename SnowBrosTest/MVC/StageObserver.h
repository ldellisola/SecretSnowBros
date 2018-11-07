#pragma once
#include "../MVC/Observer.h"
#include "../Logica/juego/Game.h"
#include "../Allegro Wrapper\AllegroSprite.h"
#include "../AllegroV2/AllegroFactory.h"
#include <stdint.h>

class StageObserver :
	public Observer
{
public:
	StageObserver(float screenH, float screenW, uint16_t groundID);
	~StageObserver();
	void draw(void *);
private:
	const uint16_t groundID;
	float screenHeigth;
	float screenWidth;
	AllegroSprite * background;
	AllegroSprite * ground;
	
};

