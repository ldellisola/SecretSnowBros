#pragma once
#include <vector>
#include <queue>
#include <stdint.h>
#include "Being.h"
#include "Projectiles/Projectile.h"
#include "Logica/Personajes/Base Classes/Shooter.h"
#include "Logica/Personajes/Projectiles/FireProjectile.h"

/*
	It is the base class for all monsters. It allows them to move acording to their directions stored on a vector.
	Derivations of this calss will only need to add directions to the vecotr in order for it to move
*/
class Monster  :
	public Being
{
public:
	Monster(uint16_t maxJumpTick, uint16_t maxWalkTick, uint16_t maxWaitTicks, uint16_t maxFallTicks, uint16_t x, uint16_t y,uint16_t ID, uint16_t scorePoints);
	virtual ~Monster ();
	virtual void chooseAction(void * ptr) = 0;

	// It updates the position of the monster . It takes a pointer to the World class
	virtual void update(void * ptr);

	virtual void setState(BeingState state);

	
	bool isFrozen();
	uint16_t getFreezeState();

	
	void collition(Being * player);
	bool collition(Projectile* proy);

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

