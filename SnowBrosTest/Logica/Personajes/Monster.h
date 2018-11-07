#pragma once
#include <vector>
#include <stdint.h>
#include "Being.h"
#include "Projectiles/Projectile.h"

//enum class CGAction { Straight, Jump, Reverse, Still, Shooting,Chase,Random };

class Monster  :
	public Being
{
public:
	Monster(uint16_t maxJumpTick, uint16_t maxWalkTick, uint16_t maxWaitTicks, uint16_t maxFallTicks, uint16_t x, uint16_t y,uint16_t ID, uint16_t scorePoints);
	~Monster ();
	virtual void chooseAction(void * ptr) = 0;
	virtual void update(void * ptr);
	void freeze();
	void unfreeze();

	virtual void setState(BeingState state);
	
	void collition(Being * player);
	void collition(Projectile* proy);

protected:
	std::vector<BeingState> futureDirections;
	uint16_t freezeState = 0;

	void updateWaitTick();
	void resetWaitTick();
	bool isWaiting();
	void startWating();
	void stopWaiting();
	uint16_t getWaitTick();
	uint16_t getPoints();

private:
	const uint16_t maxWaitTick;
	uint16_t waitTick = 0;
	const uint16_t points;
	bool waiting;
};

