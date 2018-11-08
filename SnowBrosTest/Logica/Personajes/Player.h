#pragma once
#include <vector>
#include <cstdint>
#include "Being.h"
#include "Projectiles/SnowProjectile.h"
#include "Shooter.h"
#include "../juego/Cmap.h"
#include "Score.h"

#ifdef _DEBUG
#include "../../Logger.h"

#endif

class Player :
	public Being, public Shooter<SnowProjectile>
#ifdef _DEBUG
	, protected Logger
#endif // _DEBUG
{
public:
	Player(uint16_t x, uint16_t y, uint16_t ID);
	~Player();

	void update(void * ptr);

	void collition(Projectile*proy);
	
	void setState(BeingState state);

#ifdef _DEBUG
	void kill(){
		log("Player Killed at [" + std::to_string(x) + ", " + std::to_string(y) + "]");

		Being::kill();

		if (lives > 0) {
			log("Player spawned at [" + std::to_string(x) + ", " + std::to_string(y) + "]");
		}
	}

#endif


	Score* getScoreCounter() { return &points; }


private:



	Score points;
};

