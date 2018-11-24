#pragma once
#include <vector>
#include <cstdint>
#include "Being.h"
#include "Projectiles/SnowProjectile.h"
#include "Logica/Personajes/Base Classes/Shooter.h"
#include "Logica/juego/Cmap.h"
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
	virtual ~Player();

	void update(void * ptr);

	void collition(Projectile*proy);
	
	void setState(BeingState state);

	bool isInmune() { return inmune; }

#ifdef _DEBUG
	void kill(){
		log("Player Killed at [" + std::to_string(getX()) + ", " + std::to_string(getY()) + "]");

		Being::kill();

		if (lives > 0) {
			log("Player spawned at [" + std::to_string(getX()) + ", " + std::to_string(getY()) + "]");
		}
	}

#endif
	Score* getScoreCounter() { return &points; }

	void updateInmuneTick();
	void resetInmuneTick();
	uint16_t getInmuneTick();

	
private:

	bool inmune = false;
	uint16_t inmuneTick = 0;
	const uint16_t MaxInmuneTick = 60;

	Score points;
};

