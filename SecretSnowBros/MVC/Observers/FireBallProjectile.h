#pragma once

#include "Logica/Personajes/Projectiles/FireProjectile.h"
#include "Logica/Personajes/GreenFatty.h"
#include "Observer.h"
#include <AllwAnimation/AllegroSprite.h>
#include <string>
#include <stdint.h>
//Clase que dibuja al projectil enemigo

class FireBallProjectile :
	public Observer
{
public:
	FireBallProjectile(std::string file, uint16_t blockWidth, uint16_t blockHeight) 
		:BlockHeight(blockHeight),BlockWidth(blockWidth)
	{
		sprite = new AllegroSprite(file, BlockHeight, BlockWidth);
	}
	~FireBallProjectile() {
		if (sprite !=nullptr)
			delete sprite;
	}

	void draw(void * ptr) {
		
		if (dynamic_cast<GreenFatty*>((Monster*)ptr)) {
			GreenFatty* shooter = (GreenFatty*)ptr;

			std::vector<Projectile*>& projectiles = shooter->getProjectiles();


			for (Projectile* proj : projectiles) {
				if (proj->getHorizontalDir() == HorizontalDirection::Right) {
					this->sprite->draw(proj->getX()*BlockWidth, proj->getY() * BlockHeight);
				}
				else if (proj->getHorizontalDir() == HorizontalDirection::Left) {
					this->sprite->drawHorizontallyMirrored(proj->getX()*BlockWidth, proj->getY() * BlockHeight);
				}
			}
		}
	}

private:
	AllegroSprite * sprite = nullptr;
	const uint16_t BlockWidth;
	const uint16_t BlockHeight;
};



