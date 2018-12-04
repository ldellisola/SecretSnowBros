#pragma once
#include "Observer.h"
#include <stdint.h>
#include "Logica/juego/Game.h"
#include "Logica/Personajes/SnowBall.h"
#include <vector>

#include <AllwAnimation/AllegroSprite.h>

//Clase que dibuja los proyectiles aliados
class SnowBallObserver :public Observer
{
public:
	SnowBallObserver(std::string file, uint16_t boxWidth, uint16_t boxHeight) 
		:BoxHeight(boxHeight),BoxWidth(boxWidth)
	{
		sprite = new AllegroSprite(file, boxHeight, boxWidth);
	}
	~SnowBallObserver() {
		delete sprite;
	}
	void draw(void * ptr) {

		std::vector<SnowBall*>& balls = ((Game *)ptr)->getSnowballs();

		for (SnowBall * ball : balls) {
			this->sprite->draw(ball->getX() * BoxWidth, ball->getY() * BoxHeight);
		}
		
	}
private:
	const uint16_t BoxHeight;
	const uint16_t BoxWidth;
	AllegroSprite * sprite = nullptr;
};

