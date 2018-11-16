#pragma once
#include "../Logica/Personajes/Player.h"
#include "../Logica/Personajes/Projectiles/Projectile.h"
#include "AllwAnimation/AllegroAnimation.h"
#include "Observer.h"

class ProyectileDrawer :
	public Observer
{
public:
	ProyectileDrawer(std::string proyectileSprite,uint16_t blockWidth, uint16_t blockHeight);
	~ProyectileDrawer();
	void draw(void * ptr);
private:
	AllegroSprite * bullet = nullptr;
	const uint16_t BlockWidth;
	const uint16_t BlockHeight;
};

