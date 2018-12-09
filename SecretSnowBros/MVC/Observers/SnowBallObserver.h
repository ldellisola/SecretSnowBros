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
	SnowBallObserver( uint16_t boxWidth, uint16_t boxHeight) 
		:BoxHeight(boxHeight),BoxWidth(boxWidth)
	{
		ALLEGRO_CONFIG * config = al_load_config_file("config.ini");

		sprite = new AllegroSprite(al_get_config_value(config,"SnowBallSprite","Path"), boxHeight, boxWidth);

		al_destroy_config(config);
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

