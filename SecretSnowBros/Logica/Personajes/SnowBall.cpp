#include "SnowBall.h"

#define ms50 (3)

#define JumpTicks (ms50* 24)	// 1200ms
#define WalkTicks (ms50*4)	// 200ms
#define FallTicks (ms50*6)	// 300ms
#define FrozenTicks (ms50 *200 ) // 10 segundos 200

SnowBall::SnowBall(Monster * monster, Score * PlayerScore)
	:Slider(monster->getX(), WalkTicks),Jumper(monster->getY(), JumpTicks, FallTicks),MaxFrozenTick(FrozenTicks)
{
	
	this->setHorizontalDir(HorizontalDirection::Left); //crea la bola de nieve
	setState(SnowBallState::Still);
	this->capturedMonster = monster;
	this->playerScore = PlayerScore;
	this->enemyHits = 0;
	this->wallHits = 0;
	*(this->playerScore) += 500;
}

bool SnowBall::collision(Being * being)
{

	if (this->getX() == being->getX() && this->getY() == being->getY()  ) {
		if (being->isAlive() && state == SnowBallState::Rolling) {

			if (dynamic_cast<Monster*>(being)) {
				this->enemyHits++;
				being->kill();
				for (int i = 1; i <= enemyHits; i++) {
					*(playerScore) += i * 1000;
				}
			}
			else  {
				auto player = ((Being*)being);

				if (!player->isCarried() && !player->isInmune()) {
					hijackedPlayers.push_back(being);
					player->setCarry(true);
				}
			}
			return true;
		}
	}

	return false;
}

bool SnowBall::collision(Projectile * proj) {

	if (proj->getX() == this->getX() && proj->getY() == this->getY() && getState() == SnowBallState::Still) {
		if (proj->getDistanceFromStart() == 0) {
			this->setState(SnowBallState::Rolling);
			this->setHorizontalDir(proj->getHorizontalDir());
			proj->kill();
			return true;
		}
	}
	return false;
}

bool SnowBall::collision(SnowBall * snow)
{
	if (this->getX() == snow->getX() && this->getY() == snow->getY()) {
		if (this->getState() == SnowBallState::Rolling && snow->getState() == SnowBallState::Still) {
			snow->setState(SnowBallState::Rolling);
			snow->setHorizontalDir(this->getHorizontalDir());
		}
		else if (this->getState() != SnowBallState::Rolling && snow->getState() != SnowBallState::Still) {
			this->setState(SnowBallState::Rolling);
			this->setHorizontalDir(snow->getHorizontalDir());
		}
		return true;
	}

	return false;
}

void SnowBall::update(void * ptr)
{
	if(state != SnowBallState::Rolling)
		updateFrozenTick();

	World& world = *(World *)ptr;

		for (Being * player : hijackedPlayers) {
			player->setInmune(true);
		}

	switch (getHorizontalDir())
	{
	case HorizontalDirection::Left:

		if (world.map[getY()][getX() - 1] == 'F') {
			if (getState() == SnowBallState::Rolling) {
				wallHits++;
				for (Being * player : hijackedPlayers)
					player->updateScore(200);
				if (getY() == 10) 
					wallHits = 123;
			}
			this->setHorizontalDir(HorizontalDirection::Right);




		}

		break;
	case HorizontalDirection::Right:
		if (world.map[getY()][getX() + 1] == 'F') {
				if (getState() == SnowBallState::Rolling) {
					wallHits++;
					for (Being * player : hijackedPlayers)
						player->updateScore(200);
				if (getY() == 10) 
					wallHits = 123;
			}
			this->setHorizontalDir(HorizontalDirection::Left);



		}
		break;


	}


	std::unique_ptr<char> column(new char[world.fila]);

	for (int i = 0; i < world.fila; i++) {
		column.get()[i] = world.map[i][getX()];
	}

	Jumper::update(column.get());

	std::unique_ptr<char> row(new char[world.columna]);

	for (int i = 0; i < world.columna; i++) {
		row.get()[i] = world.map[getY()][i];
	}

	Slider::update(row.get());

	for (Being* plyr : hijackedPlayers) {
		if (plyr->getState() == BeingState::Jumping) {
			releasePlayer(plyr);

		}
		else {
			plyr->setX(getX());
			plyr->setY(getY());
		}
	}
}


void SnowBall::setState(SnowBallState state) {

	switch (state)
	{
	case SnowBallState::Carried:
		break;
	case SnowBallState::Rolling:
		this->setHorizontalState(HorizontalState::Moving);
		break;
	case SnowBallState::Still:
		this->setHorizontalState(HorizontalState::Still);
		break;
	default:
		break;
	}
	this->state = state;



}

void SnowBall::updateFrozenTick()
{
	frozenTick++;
}

void SnowBall::resetFrozenTick()
{
	frozenTick = 0;
}

uint16_t SnowBall::getFrozenTick()
{
	return frozenTick;
}
#include <iostream>

void SnowBall::releasePlayer(Being * player)
{
	try {
		player->setCarry(false);
		player->setInmune(true);
		

		for (int i = (int)hijackedPlayers.size() - 1; i >= 0; i--)
		{
			if (hijackedPlayers[i] == player)
				hijackedPlayers.erase(hijackedPlayers.begin() + i);
		}
	}
	catch (...) {
		std::cout << "Fuck";
	}


}

bool SnowBall::shouldDie()
{
	if (wallHits >= maxHits) {
		return true;
	}
	else 
		return false;
}

bool SnowBall::shouldMelt()
{
	if (getFrozenTick() == MaxFrozenTick)
		return true;
	else
		return false;
}

Monster * SnowBall::melt()
{
	capturedMonster->revive();
	capturedMonster->setX(getX());
	capturedMonster->setY(getY());
	for (Being * player : hijackedPlayers)
		releasePlayer(player);

	return this->capturedMonster;
}

std::vector<Being*>& SnowBall::getHijackedPlayers()
{
	return this->hijackedPlayers;
}

SnowBall::~SnowBall ()
{
	for (Being * being : hijackedPlayers)
		releasePlayer(being);
}
