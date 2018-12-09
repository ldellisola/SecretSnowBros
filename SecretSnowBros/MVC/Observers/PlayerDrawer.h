#pragma once
#include "Observer.h"
#include "AllwAnimation/AllegroAnimation.h"
#include "Logica/Personajes/Being.h"
#include"Logica/juego/Game.h"

 //CLase que dibuja al jugador
class PlayerDrawer :
	public Observer
{
public:
	PlayerDrawer(uint16_t blockWidth, uint16_t blockHeight);
	~PlayerDrawer();

	void loadObserver(Observer* obs);

	void loadObserver(Observer&obs);
	
	void loadPlayerSprite();

	void draw(void * data);
private:
	std::vector<AllegroSprite*> sprites;
	const uint16_t BlockWidth;
	const uint16_t BlockHeight;

	std::vector<Observer*> observers;
};



