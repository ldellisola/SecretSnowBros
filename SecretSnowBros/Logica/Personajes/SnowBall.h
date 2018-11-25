#pragma once
#include <vector>

#include "Logica/Personajes/Player.h"
#include "Logica/Personajes/Monster.h"
#include "Logica/Personajes/Base Classes/Slider.h"
#include "Logica/Personajes/Base Classes/Jumper.h"
#include "Logica/juego/Cmap.h"

enum class SnowBallState
{
	Carried, Rolling, Still
};

class SnowBall :public Slider,public Jumper
{
public:
	SnowBall(Monster * monster, Score * PlayerScore);

	bool collision(Being * being);

	bool collision(Projectile * proj);

	void update(void * ptr);

	bool shouldDie();

	bool shouldMelt();

	Monster * melt();



	virtual ~SnowBall();
protected:
	const uint16_t maxHits = 8;

	void setState(SnowBallState state);

	void updateFrozenTick();
	void resetFrozenTick();
	uint16_t getFrozenTick();

private:

	void releasePlayer(Player * player);

	uint16_t wallHits,enemyHits;
	SnowBallState state;
	HorizontalDirection direction;
	Monster * capturedMonster = nullptr;
	Score * playerScore = nullptr;

	std::vector<Player *> hijackedPlayers;

	uint16_t frozenTick;
	const uint16_t MaxFrozenTick;
};

