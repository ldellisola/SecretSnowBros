#pragma once
#include <vector>
#include <queue>
#include <stdint.h>
#include "Being.h"
#include "Projectiles/Projectile.h"
#include "Logica/Personajes/Base Classes/Shooter.h"
#include "Logica/Personajes/Projectiles/FireProjectile.h"


class Monster  :
	public Being
{
public:
	Monster(uint16_t maxJumpTick, uint16_t maxWalkTick, uint16_t maxWaitTicks, uint16_t maxFallTicks, uint16_t x, uint16_t y,uint16_t ID, uint16_t scorePoints);
	virtual ~Monster ();
	virtual void chooseAction(void * ptr) = 0;
	virtual void update(void * ptr);


	virtual void setState(BeingState state);

	
	bool isFrozen();
	uint16_t getFreezeState();

	
	void collition(Being * player);
	void collition(Projectile* proy);

protected:




	std::queue<BeingState> futureDirections;

	void updateWaitTick();
	void resetWaitTick();
	uint16_t getWaitTick();
	bool isWaiting();
	void startWating();
	void stopWaiting();

	void freeze();
	void unfreeze();
	void updateFreezeTick();
	void resetFreezeTick();
	uint16_t getFreezeTick();
	const uint16_t maxWaitTick;
	const uint16_t maxFrozenTick;
	const uint16_t points;

	
	uint16_t getPoints();

private:
	uint16_t waitTick = 0;
	uint16_t freezeState = 0;


	uint16_t freezeTick = 0;


	bool waiting;
};

