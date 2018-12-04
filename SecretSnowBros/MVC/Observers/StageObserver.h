#pragma once
#include "Observer.h"
#include "Logica/juego/Game.h"
#include "AllwAnimation/AllegroSprite.h"
#include "AllwInit/AllegroFactory.h"
#include <stdint.h>
//Encargado de dibujar el mapa
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

