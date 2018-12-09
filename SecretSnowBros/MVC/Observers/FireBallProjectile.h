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
	FireBallProjectile( uint16_t blockWidth, uint16_t blockHeight) 
		:BlockHeight(blockHeight),BlockWidth(blockWidth)
	{

		ALLEGRO_CONFIG *config = al_load_config_file("config.ini");

		sprite = new AllegroSprite(al_get_config_value(config,"FireProjectileSprite","Path"), BlockHeight, BlockWidth);

		al_destroy_config(config);
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



