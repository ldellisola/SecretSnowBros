#include "SnowBall.h"



SnowBall::SnowBall(Monster * monster, Score * PlayerScore)
{
	this->x = monster->getX();
	this->y = monster->getY();
	//this->direction = monster->getHorizontalDir();
	this->state = SnowBallState::Still;
	this->capturedMonster = monster;
	this->playerScore = PlayerScore;
	this->enemyHits = 0;
	this->wallHits = 0;
}

bool SnowBall::collision(Being * being)
{
	if (dynamic_cast<Monster*>(being)) {

		if (this->x == being->getX() && this->y == being->getY()) {

			this->enemyHits++;

			for (int i = 1; i <= enemyHits; i++) {
				*playerScore += i * 1000;
			}

			return true;
		}

	}
	else if (dynamic_cast<Player *>(being)) {

		if (this->x == being->getX() && this->y == being->getY()) {

			hijackedPlayers.push_back((Player*)being);

		}

		return true;

	}
	return false;
}

void SnowBall::update(void * ptr)
{

	World * world = (World *) ptr;





}

bool SnowBall::shouldDie()
{
	if (wallHits == maxHits)
		return true;
	else 
		return false;
}

SnowBall::~SnowBall ()
{
}
