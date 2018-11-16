#pragma once
#include "Observer.h"
#include "AllwAnimation/AllegroAnimation.h"
#include "../Logica/Personajes/Being.h"
#include"../Logica/juego/Game.h"


class PlayerDrawer :
	public Observer
{
public:
	PlayerDrawer(std::string file,uint16_t blockWidth, uint16_t blockHeight);
	~PlayerDrawer(){}

	void loadObserver(Observer* obs);

	void loadObserver(Observer&obs);

	void draw(void * data);
private:
	AllegroSprite sprite;
	const uint16_t BlockWidth;
	const uint16_t BlockHeight;

	std::vector<Observer*> observers;
};



