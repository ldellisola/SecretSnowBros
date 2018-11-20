#pragma once
#include <vector>

#include "Logica/Personajes/Player.h"
#include "Logica/Personajes/Monster.h"
#include "Logica/juego/Cmap.h"

enum class SnowBallState
{
	Carried, Rolling, Still
};

class SnowBall
{
public:
	SnowBall(Monster * monster, Score * PlayerScore);

	bool collision(Being * being);

	void update(void * ptr);

	bool shouldDie();



	~SnowBall();
protected:
	const uint16_t maxHits = 8;
	const uint16_t MaxRollTicks = 20;
private:
	uint16_t x, y, wallHits,enemyHits, rollTicks;
	SnowBallState state;
	BeingDirection direction;
	Monster * capturedMonster = nullptr;
	Score * playerScore = nullptr;

	std::vector<Player *> hijackedPlayers;
};

